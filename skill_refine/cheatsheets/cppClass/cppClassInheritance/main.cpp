// #include "./Base.h"
#include "./Derived.h"


// 문제: 
// 1. 정적바인딩문제: 기본클래스의 멤버가 virtual로 선언되지 않았고, 파생클래스가 override하지 않아 몇몇 행동이 제대로 작동하지 않는다.
// 2. 객체썰림: 파생클래스의 멤버/메서드 등이 기본클래스로 선언되면(참조선언이 아님) 메모리 할당시 파생클래스의 추가내용은 버려진다.

// 해결:
// 1. 정적캐스팅: 선언은 기본클래스로 "참조선언"하고 할당은 파생객체로 할당 후, 파생타입 참조선언으로 다시 캐스팅한다.
// 2. 행동 재정의가 필요하다면 기본클래스를 추상클래스, 인터페이스 클래스로 만든다.
// 3. 애초에 파생클래스타입/파생클래스 할당을 사용한다.

int main(int argc, char* argv[]) {

    // 기본클래스로의 사용은 문제없다.
    Base* b = new Base(1, "ted");
    Base b2 = Base(2, "park");
    b->getInfo();
    b2.getInfo();


    // 기본클래스로 참조된 파생클래스
    // 정적바인딩 문제: 객체 썰림은 발생하지 않는다. b3타입은 Derived의 메모리를 참조하고 있기 때문. 하지만 메서드 기능들이 원치않게 작동한다.
    Base* b3 = new Derived(3, "park", 190.3);
    b3->getInfo();              // 순수 가상클래스가 아니라서 Base의 getInfo() 가 호출됨: 정적바인딩 문제.
    // b3->sayHello();          // 당연히 쓸 수 없다. java 등 공통임.


    // 굳이 고쳐서 사용하려면? 
    // 정적캐스팅: b3를 정상사용 하려면 재참조 해야함. static_cast를 이용해야한다. &b3 이런거 안됨.
    Derived* fixB3 = static_cast<Derived*>(b3);
    fixB3->getInfo();
    fixB3->sayHello();

    // dynamic_cast: 동적캐스팅은 런타임에 타입을 확인하고 기본클래스가 최소 하나라도 virtual로 선언되어야 사용할 수 있으며 이순간 추상클래스에 해당됨.


    // 파생선언/파생할당은 문제없음.
    Derived d1 = Derived(4, "PARK",  159.6);
    d1.getInfo();
    d1.sayHello();              // 사용가능.


    // 객체 썰림 현상: 참조하지 않으면 객체썰림이 일어나 height를 사용할 수 없으며, 동적바인딩 되지 않은 sayHello는 사용할 수 없다.
    // 이미 더 작은공간의 메모리로 할당해 메모리가 손상되어 어떤 방법을 써도 Derived의 추가기능은 쓸 수 없다.
    Base d2 = Derived(5, "TEST", 3.14);
    d2.getInfo();
    // d2.sayHello();


    // 이것을 해결하려면 동적바인딩: virtual로 선언된 멤버메서드를 사용하도록 한다. Abstract 나 Interface를 참고하도록.



    delete b;
    delete b3;
    delete fixB3;
    return 0;
}