#include <iostream>

int main(int argc, char* argv[]) {

    int a = 3;
    auto b = [](const int& n) {
        return n * n;
    };

    std::cout << b(a) << a ;
    return 0;
}