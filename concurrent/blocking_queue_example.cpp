#include <chrono>
#include <iostream>
#include <thread>

#include "blocking_queue.cpp"
#include "blocking_queue.h"

void push_data(blocking_queue<int>& queue) {
    for (int i = 0; i < 5; i++) {
        queue.push(i);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void display(blocking_queue<int>& queue) {
    while (true) {
        std::shared_ptr<int> p = queue.wait_and_pop();
        if (p != nullptr) {
            std::cout << *p << std::endl;
        }
    }
}

int main(int argc, char const* argv[]) {
    blocking_queue<int> queue;
    std::thread t1{[&] { push_data(queue); }};
    std::thread t2{[&] { display(queue); }};
    t1.detach();
    t2.detach();
    std::this_thread::sleep_for(std::chrono::seconds(6));
    return 0;
}
