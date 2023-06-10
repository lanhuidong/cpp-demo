#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

template <typename T>
class blocking_queue {
   public:
    blocking_queue() = default;
    blocking_queue(blocking_queue const&);
    blocking_queue& operator=(blocking_queue const&) = delete;
    void push(T elem);
    bool try_pop(T& elem);
    std::shared_ptr<T> try_pop();
    void wait_and_pop(T& elem);
    std::shared_ptr<T> wait_and_pop();
    bool empty() const;

   private:
    mutable std::mutex mutex_;
    std::queue<T> elems_;
    std::condition_variable cv_;
};