#include <iostream>

void print(int* ptr) {
    std::cout << "*ptr : "<<*ptr << "  ptr : " << ptr << std::endl;
}


int main() {
    int a, b, c;
    a = 10;
    b = 20;
    c = 30;
    int* p;
    p = &a;
    print(p);
    p = &b;
    print(p);
    p = &c;
    print(p);

    return 0;
}