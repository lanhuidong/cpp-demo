/*
 * 如果编译器还不支持module，那么模版代码应该推荐采用Inclusion Model，即声明和定义写在一个文件里
 */
#include <cassert>
#include <ostream>
#include <string>
#include <vector>

// 方案二
template <typename T>
class Stack;
template <typename T>
std::ostream& operator<<(std::ostream&, Stack<T> const&);

template <typename T>
class Stack {
   public:
    Stack() = default;
    Stack(T elem) : elems({std::move(elem)}) {}
    ~Stack() = default;
    Stack(Stack const&) = default;             // 等价于Stack(Stack<T> const&) = default
    Stack& operator=(Stack const&) = default;  // 等价于Stack<T>& operator=(Stack<T> const&) = default
    void push(T const& elem) {
        elems.push_back(elem);
    }
    void pop() {
        assert(!elems.empty());
        elems.pop_back();
    }

    T const& top() {
        assert(!elems.empty());
        return elems.back();
    }

    bool empty() {
        return elems.empty();
    }

    void printOn(std::ostream& strm) const {
        for (T const& elem : elems) {
            strm << elem << " ";
        }
    }
    /* 方案一
    template <typename U>
    friend std::ostream& operator<<(std::ostream& strm, Stack<U> const& s) {
        s.printOn(strm);
        return strm;
    }*/
    friend std::ostream& operator<< <T>(std::ostream& strm, Stack<T> const& s) {
        s.printOn(strm);
        return strm;
    }

   private:
    std::vector<T> elems;
};

// c++17 deduction guide, 当元素为char const*时，Stack会被推断为Stack<std::string>
Stack(char const*) -> Stack<std::string>;