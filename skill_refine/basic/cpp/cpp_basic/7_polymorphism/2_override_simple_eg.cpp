#include <iostream>
using namespace std;

/* 동적 바인딩 3가지 조건.
▪ 상속
▪ 기본 클래스 포인터 또는 참조자
▪ 가상 함수
*/


class Base {
public:
    virtual void move() {  // 가상 함수
        cout << "exec: Base move" << endl;
    }
    virtual ~Base();    // 가상 소멸자.
};

class Derived : public Base {
public:
    void move() override {  // 가상 함수 재정의
        cout << "exec: Derived move" << endl;
    }
    // virtual move() {} 와 같은 형태로 사용해도 되고, move()처럼 기존의 생성자 처럼 사용해도 되나, virtual을 적는것을 권장. override도 권장되는 방법.

    ~Derived() override;
};

Base::~Base(){std::cout << "msg: Base destructor called" << std::endl;}
Derived::~Derived(){std::cout << "msg: Derived destructor called" << std::endl;}

int main() {
    Base b;  // 기본 클래스 객체 생성
    b.move();  // Base의 move()가 호출됨

    // 역참조로 동적할당 사용시. - 포인터를 써야 동적바인딩 조건을 만족함.
    Base* p = new Derived();  // 기본 클래스 포인터로 유도 클래스 객체 가리킴
    p->move();  // Derived의 move()가 호출됨
    
    delete p;

    // 참조자 사용시에도 Base 타입의 구애를 받지 않고 사용가능.
    p = &b;
    p->move();


    

    return 0;
}
