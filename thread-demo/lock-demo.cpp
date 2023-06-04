#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

std::vector<std::string> names;
std::mutex m;
std::mutex m2;

void addNames(std::string name) {
    std::lock_guard lock(m);
    names.emplace_back(name);
}

std::size_t getNameNumber() {
    // std::scoped_lock()和std::lock_guard()效果是等价的，但是前者可以同时获取多个锁
    std::scoped_lock lock(m, m2);  // c++17
    return names.size();
}

// 和getNameNumber等价
std::size_t getNameNumbers() {
    std::lock(m, m2);
    std::lock_guard lock1(m, std::adopt_lock);
    std::lock_guard lock2(m2, std::adopt_lock);
    return names.size();
}

void deferLock() {
    // std::unique_lock比lock_guard更灵活，但是也略慢，并且占用更多空间
    std::unique_lock lock{m, std::defer_lock};
    // 其他语句
    lock.lock();
}

int main(int argc, char const* argv[]) {
    std::thread t1{addNames, "LanZilin"};
    std::thread t2{addNames, "LanYucheng"};
    t1.join();
    t2.join();
    std::lock_guard lock(m);
    for (auto& name : names) {
        std::cout << name << std::endl;
    }
    return 0;
}
