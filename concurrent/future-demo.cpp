#include <chrono>
#include <future>
#include <iostream>
#include <thread>

void do_time_comsuing_work() {
    std::cout << "start do" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main(int argc, char const* argv[]) {
    std::future<void> done = std::async(do_time_comsuing_work);
    done.get();
    std::cout << "task done!" << std::endl;

    std::packaged_task task(do_time_comsuing_work);
    std::future result = task.get_future();
    task();
    result.get();
    std::cout << "task done!" << std::endl;

    done = std::async(do_time_comsuing_work);
    auto sf = done.share();
    std::thread t1{[=] {
        sf.get();
        std::cout << "t1 done" << std::endl;
    }};
    std::thread t2{[=] {
        sf.get();
        std::cout << "t2 done" << std::endl;
    }};
    t1.join();
    t2.join();
    return 0;
}
