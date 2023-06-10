#include "blocking_queue.h"

template <typename T>
blocking_queue<T>::blocking_queue(blocking_queue<T> const& other) {
    std::lock_guard lock(other.mutex_);
    elems_ = other.elems_;
}

template <typename T>
void blocking_queue<T>::push(T elem) {
    std::lock_guard lock(mutex_);
    elems_.push(elem);
    cv_.notify_all();
}

template <typename T>
void blocking_queue<T>::wait_and_pop(T& elem) {
    std::unique_lock lock(mutex_);
    cv_.wait(lock, [this] { return !elems_.empty(); });
    elem = elems_.front();
    elems_.pop();
}

template <typename T>
std::shared_ptr<T> blocking_queue<T>::wait_and_pop() {
    std::unique_lock lock(mutex_);
    cv_.wait(lock, [this] { return !elems_.empty(); });
    std::shared_ptr<T> res{std::make_shared<T>(elems_.front())};
    elems_.pop();
    return res;
}

template <typename T>
bool blocking_queue<T>::try_pop(T& elem) {
    std::lock_guard lock(mutex_);
    if (elems_.empty()) {
        return false;
    }
    elem = elems_.front();
    elems_.pop();
    return true;
}

template <typename T>
std::shared_ptr<T> blocking_queue<T>::try_pop() {
    std::lock_guard lock(mutex_);
    if (elems_.empty()) {
        return std::shared_ptr<T>{};
    }
    std::shared_ptr<T> res{std::make_shared<T>(elems_.front())};
    elems_.pop();
    return res;
}

template <typename T>
bool blocking_queue<T>::empty() const {
    std::lock_guard lock(mutex_);
    return elems_.empty();
}
