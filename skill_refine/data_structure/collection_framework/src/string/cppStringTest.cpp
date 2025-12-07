#include <iostream>

int main() {

    std::string a = "Hello";
    std::string b = "Hello";
    std::string c = "World";

    // cpp 는 java의 ==과는 다르게 값비교가 됨.
    // java는 equals
    std::cout << (a == b) << (b == c) << std::endl;
    return 0;
}