/*
 * 只有初始化时需要保护，后续可并发访问
 */
#include <iostream>
#include <map>
#include <shared_mutex>
#include <string>

std::shared_ptr<std::string> resource_ptr;
std::once_flag init_flag_;
void init_resource() {
    resource_ptr.reset(new std::string("xxxx"));
}

class X {
   public:
    void display() {
        std::cout << "X" << std::endl;
    }
};

X& getXInstance() {
    // C++11规定静态数据初始化只会在某一线程上单独发生，
    // 初始化完成之前，其他线程不会越过声明语句继续执行
    static X instance;
    return instance;
}

class dns_cache {
   private:
    std::map<std::string, std::string> entries;
    mutable std::shared_mutex mutex;

   public:
    std::string find_entry(const std::string& domain) const {
        std::shared_lock lock(mutex);
        const auto it = entries.find(domain);
        return it == entries.end() ? "" : it->second;
    }

    void update_entry(const std::string& domain, const std::string& ip) {
        std::lock_guard lock(mutex);
        entries[domain] = ip;
    }
};

int main(int argc, char const* argv[]) {
    std::call_once(init_flag_, init_resource);
    resource_ptr->size();

    getXInstance().display();
    return 0;
}
