#include <iostream>

// 정적바인딩 예제.

class Base {

protected:
    int val;

public:
    Base() {
        val = 1;
    }
    void SayHello() {
        std::cout<< "Hello Base" << std::endl;
    }
    void printVal() {
        std::cout << "val : " << val << std::endl;
    }    

};

class Derived: public Base {

public:
    Derived() {
        val = 2;
    }

    void SayHello() {
        std::cout<< "Hello Derived" << std::endl;
    }


};

int main () {
    Base a;
    a.SayHello();
    Derived b;
    b.SayHello();

    a.printVal();

    a = b;
    a.SayHello();       // 소용없이 a클래스 기준의 SayHello 메서드로 정적바인딩 됨.

    Base *c = new Derived{};
    c->SayHello();      // 마찬가지로 Base 기준의 SayHello 메서드 호출됨.
                        // 동적바인딩시 Derived 객체의 SayHello 호출시킬 수 있음.
                        // 정적: 컴파일시 호출될 타입 결정  (현재 예로 Base 클래스 기준)
                        // 동적: 런타임에서 메모리에 저장된 기준으로 호출함수 결정.

    a.printVal();
    b.printVal();
    c->printVal();

    delete c;


    return 0;
}

