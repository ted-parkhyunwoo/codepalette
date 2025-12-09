#include "Concrete.h"


int main() {
    Abstract* test = new Concrete(3, "Ted");

    std::cout << test->getId() << std::endl;
    test->sayHello();
    test->sayHi();

    // 추상클래스가 순수가상함수를 포함한다면 객체로 만들 수 없다.
    // Abstract test2 = Abstract(3);
    

    delete test;
    return 0;
}