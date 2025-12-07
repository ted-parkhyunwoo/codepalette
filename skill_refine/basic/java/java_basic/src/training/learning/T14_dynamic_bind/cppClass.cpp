#include <iostream>

// CPP 동적바인딩 예제: Dynamic Binding.

/* 참고:
기본클래스가 순수가상함수를 포함하면 추상클래스. 순수가상함수로만 구현되면 인터페이스클래스.
자식클래스가 추상클래스를 상속하면 구체클래스, 인터페이스클래스를 상속하면 인터페이스구현클래스.
아래에는 추상클래스의 느낌과 구체클래스의 느낌을 따를 뿐, 일반 부모/자식클래스임.
*/


// 기본클래스:기본함수에는 가상함수로 선언: virtual.
class Base {
    public:
        virtual void whatIsThis() { std::cout << "Base\n"; }
        // override금지하려면 final
        virtual void couldNotChange() final { std::cout << "override 금지\n"; }
        // 모순점: virtual 로 override 허용, final로 불허인데, 이 의미는 다형성의 틀에서 이것만큼은 override하지마라는 경고의미정도로 이해할 것.
};
// 파생클래스:override선언.
class Derived: public Base {
    public:
        void whatIsThis() override { std::cout << "Derived\n"; }
};

int main() {
    // 사용할 때에 따라서도 동적/정적 구분하여 사용 가능하다.

    Derived test;
    test.whatIsThis();      // Derived

    Base test2;
    test2.whatIsThis();     // Base

    Base* test3 = &test;
    test3->whatIsThis();    // Derived

    Base* test4 = new Derived();
    test4->whatIsThis();    // Derived
    delete(test4);

    Base& test5 = test;
    test5.whatIsThis();     // Derived

    Base test6 = (Derived)test;
    test6.whatIsThis();     // Base

    Base* test7 = dynamic_cast<Base*>(&test);
    test7->whatIsThis();    // Derived

    test7->couldNotChange();

    /* 정리
    기본타입에 파생객체를 참조하면 파생객체의 특성을 따름.
    기본타입에 파생객체를 선언하면 slicing이 일어남(파생객체 특성 상실)
    */
    
    return 0;
}