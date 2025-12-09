// #include "./Base.h"
#include "./Derived.h"


int main(int argc, char* argv[]) {

    Base* b = new Base(1, "ted");
    Base b2 = Base(2, "park");

    b->getInfo();
    b2.getInfo();

    Base* b3 = new Derived(3, "park");
    b3->getInfo();              // 순수 가상클래스가 아니라서 Base의 getInfo() 가 호출됨!
    // b3->sayHello();          // 당연히 쓸 수 없다. java 등 공통임.

    Derived d1 = Derived(4, "PARK",  159.6);

    d1.getInfo();
    d1.sayHello();              // 사용가능.

    delete b;
    delete b3;
    return 0;
}