#include <iostream>

// namespace는 C++에서 코드의 범위를 구분하는 데 사용됩니다.
// namespace는 코드의 충돌을 방지하고, 코드를 더 잘 조직할 수 있도록 도와줍니다.
namespace My_Code {
    class MyClass {
    public:
        void myFunction() {}
        MyClass() {};
    };
    
    double a = 3.14;

    int main();
}

void My_Code::MyClass::myFunction() {
    std::cout << "MyClass::myFunction()" << std::endl;
}

int My_Code::main() {
    std::cout << My_Code::a << std::endl;
    return 0;
}
