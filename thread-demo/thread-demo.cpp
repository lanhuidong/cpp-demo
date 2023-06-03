#include <chrono>
#include <iostream>
#include <thread>

class background_task {
   private:
    void do_something() const {
        std::cout << "do something!" << std::endl;
    }

   public:
    void operator()() const {
        do_something();
    }
};

void printName(std::string& name) {
    std::cout << "name: " << name << std::endl;
}

int main(int argc, char const* argv[]) {
    // 硬件并发线程数，可能返回0
    std::cout << "hardware concurrency number: " << std::thread::hardware_concurrency() << std::endl;

    std::thread thread_1_{background_task()};
    std::thread thread_2_{[] { std::cout << "lambda" << std::endl; }};

    // thread对象没关联线程时返回的ID
    std::thread no_thead_attach;
    std::cout << no_thead_attach.get_id() << std::endl;
    // 获取当前线程ID
    std::cout << "current thread id: " << std::this_thread::get_id() << std::endl;

    // 获取制定线程ID
    std::cout << "thread_1_ id: " << thread_1_.get_id() << std::endl;
    std::cout << "thread_2_ id: " << thread_2_.get_id() << std::endl;

    std::cout << std::boolalpha << thread_1_.joinable() << std::endl;
    thread_1_.join();
    std::cout << std::noboolalpha << thread_1_.joinable() << std::endl;
    thread_2_.join();

    std::thread t1{[] { std::this_thread::sleep_for(std::chrono::seconds(2)); }};
    std::thread t2{[] { std::this_thread::sleep_for(std::chrono::seconds(2)); }};
    // t1 = std::move(t2); 这里不能赋值，否则t1回调用std::terminate()终止线程
    t1.join();
    t2.join();

    std::string name = "Lan";
    // 传递引用数据要用std::ref()，否则编译不通过
    std::thread t3{printName, std::ref(name)};
    t3.join();
    return 0;
}
