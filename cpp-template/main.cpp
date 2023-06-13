#include <iostream>

#include "stack.hpp"

int main(int argc, char const* argv[]) {
    Stack<int> stack;
    stack.push(1);
    std::cout << stack << std::endl;
    return 0;
}
