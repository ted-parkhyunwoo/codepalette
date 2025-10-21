#include <iostream>

// 우리가 작성했던 코드들은 이미 구상클래스. (concrete class.)

struct Entity {  // 순수가상함수 포함됐으므로, 추상클래스임.(abstract class.)
public:
    // pure virtual function.
    virtual void func() const = 0; // = 0; 이면 순수가상함수로 사용. (즉 몸체{}가 없는 함수.)
    // virtual void func() const{};        // 이런 식으로도 작성해도 작동 가능하나, 이럴 경우 객체 생성이 가능해져버림. private처럼 강력한 제약을 두기 위해 = 0;을 따라야 함.
    virtual ~Entity();          //? 순수가상소멸자 이상하게 구현을 해줘야함. =0; 대신 {}로 구현해도 됨. 추상클래스도 여전히 소멸자는 반드시 구현되어야 함.
};

Entity::~Entity(){
    std::cout << "Abstract Entity Class destructor called." << std::endl;
    } // Entity의 순수 가상 소멸자 구현.


// Entity는 단순히 포함된 멤버 함수가 순수가상함수를 포함하면 abstract class (추상클래스) 가 되므로, 객체생성 불가.


class Derived: public Entity {
public:

    //! 순수가상함수는 유도클래스에서 무조건 func()를 오버라이드 해서 무조건 작성하도록 강제할 수 있다는 의미.

    virtual void func() const override {
        std::cout << "Derived function runned." << std::endl;
    }
    virtual ~Derived() override {
        std::cout << "Derived destructor called." << std::endl;
    }
};


int main() {
    // Entity a;    // 추상클래스라서 객체 생성 불가.
    Entity* a = new Derived{};      // 다만 역참조, 참조자 사용시 동적바인딩 함수 호출 사용은 여전히 가능함. 
    a->func();  //Derived로 동적바인딩 된 func 호출 가능.
    delete a;

    const Derived b;
    b.func();

    return 0;
}
