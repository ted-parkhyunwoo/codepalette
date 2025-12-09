#include "Concrete.h"


int main() {
    Abstract* test = new Concrete(3, "Ted");

    std::cout << test->getId() << std::endl;
    test->sayHello();

    // 동적바인딩 사용: 부모/자식클래스에서는 기본클래스선언, 자식클래스 할당 인스턴스가 객체 slicing(객체썰림) 문제를 일으켰지만, 추상클래스/인터페이스 클래스에서는 virtual함수(가상함수/순수가상함수)를 완벽히 override 대체해 해결한다
    test->sayHi();

    // 추상클래스가 순수가상함수를 포함한다면 객체로 만들 수 없다.
    // Abstract test2 = Abstract(3);
    

    delete test;
    return 0;
}