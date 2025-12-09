#include <iostream>

// 인터페이스 : 정적멤버들 외 멤버변수는 없으며, 순수가상함수로만 이루어짐. 밑그림만 그려주고 모두 직접 구현하도록함
class Interface {
    protected:
        static const int DAYS = 365;        // protected 되어, 직접접근 불가. static멤버라 인터페이스클래스가 아직 확실

    public:
        virtual void sayHello() = 0;        // 순수가상함수
        static void sayHi() {std::cout << "HI\n"; }     // static메서드이므로 인터페이스 클래스임이 유효.
};