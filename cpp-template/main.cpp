#include <iostream>

#include "stack.hpp"

template <typename T>
struct ValueWithComment {
    T value;
    std::string comment;
};

// c++ 17 deduction guide
ValueWithComment(char const*, char const*) -> ValueWithComment<std::string>;

int main(int argc, char const* argv[]) {
    Stack<int> stack;
    stack.push(1);
    std::cout << stack << std::endl;
    Stack stringStack{"haha"};
    std::cout << stringStack << std::endl;
    ValueWithComment vc = {"Hello", "World"};
    return 0;
}
