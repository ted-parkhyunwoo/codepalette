#include <iostream>

class TestClass {
private:
    int a;
    int b;
public:
    TestClass(int a, int b) : a(a), b(b) {
        std::cout << "init complete" << std::endl;
    }

    virtual void PrintValues() {
        std::cout << a << "," << b << std::endl;
    }

    virtual ~TestClass() {
        std::cout << "TestClass destructor called" << std::endl;
    }

};


int main() {

    TestClass* tPtr = new TestClass(1, 2);
    tPtr->PrintValues();

    delete tPtr;
    return 0;
}
