#include "Impements.h"

int main() {

    // 인터페이스의 인스턴스 생성없이 정적 멤버를 호출 가능한건 java, dart와 동일
    Interface::sayHi();                      

    // 순수 가상클래스(인터페이스클래스)의 구현 사용시 참조객체선언 해야함
    Interface* test = new Implements(3);             
    // std::cout << test->DAYS << std::endl;        // DAYS 스태틱 상수는 protected 되어 직접접근 불가. (구현체에서만 접근 가능)
    test->sayHello();

    // 혹은 test2(Implements) 인스턴스를 Interface 로 참조 (기본/파생 예제처럼 정적캐스팅 할 필요 없이 편하게 test2를 ref할 수 있다.)
    Implements test2 = Implements(4);
    Interface* test3 = &test2;
    test3->sayHello();

    std::cout << test2.getDays() << std::endl;

    test->sayHi();
    test2.sayHi();
    test3->sayHi();

    delete test;
    return 0;
}