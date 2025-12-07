#include <iostream>

template<typename T>
void print(T userInput) {
    std::cout << userInput << std::endl;
}

int main() {

    int a = 3;
    double b = 3.14;
    char c = 'c';
    std::string d = "abc";

    print(a);
    print(b);
    print(c);
    print(d);

    return 0;
}