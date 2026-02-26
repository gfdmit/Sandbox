#include <iostream>
#include <string>

void replaceX(std::string& s_, std::string x_) {
    auto pointer = s_.find('x');
    while (pointer != std::string::npos) {
        s_.replace(pointer, 1, x_);
        pointer = s_.find('x');
    }
}

int main() {
    std::string s_ = "sin(x) + x^2 - x";
    replaceX(s_, "13.7");
    std::cout << s_;
}