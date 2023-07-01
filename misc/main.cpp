#include <iomanip>
#include <iostream>
#include <vector>

void printHex(const std::vector<char>& v) {
    int i{0};
    std::cout << std::hex;
    for (auto c : v) {
        std::cout << std::setw(2) << std::setfill('0') << (0xff & (unsigned int)c) << " ";
        i++;
        if (i % 10 == 0) {
            std::cout << std::endl;
        }
    }
}

int main(int argc, char const* argv[]) {
    std::vector<char> chars;
    for (int i = 0; i < 256; i++) {
        chars.emplace_back((char)i);
    }
    int i = 0;
    for (auto c : chars) {
        std::cout << c << " ";
        i++;
        if (i % 10 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

    printHex(chars);
    std::cout << std::endl;
    return 0;
}
