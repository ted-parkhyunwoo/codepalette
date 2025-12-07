#include <iostream>

class Entity {
protected:
    int x;
    int y;
public:
    Entity(int x, int y) : x(x), y(y) {}


    virtual void Move(int dx, int dy) { 
    // 가상함수 선언. 유도클래스에서 오버라이딩 사용 가능하게됨.
    // 오버라이드 조건으로 유도클래스에서도 반환타입, 함수이름, 매개변수 이름이 똑같아야 함.
        x += dx;
        y += dy;
    }


    void PrintPosition() {
        std::cout << x << "," << y << std::endl;
    }

    //중요! Entity* 타입을 사용하여 Player 유도클래스를 동적할당 객체로 삼을 때를 대비하여 소멸자도 가상함수로 구현해야 함. 이것을 작성 안하면 warning 발생!
    virtual ~Entity(){
        std::cout << "Entity destructor called" << std::endl;
    }

};

class Player : public Entity {

private:
    int hp;
    int xp;
public:
    Player(int x, int y, int hp, int xp) : Entity(x, y), hp{hp}, xp{xp} {}


    virtual void Move(int dx, int dy) {
    // 유도클래스에는 virtual을 쓰나 안쓰나 기능상 상관없으나, 관습상 표기해줘야함.
        x += dx * 2;
        y += dy * 2;
    }
    // 추가적으로 키워드를 작성하는 방법도 있음
    // void Move(int dx, int dy) override {};


    // 마찬가지로 유도클래스의 소멸자도 가상함수로 표기해주는 것이 관습.
    virtual ~Player(){
        std::cout << "Player destructor called" << std::endl;
    }

};


int main() {
    Entity* ePtr = new Player{1,1,10,10};
    
    // 정적 바인딩의 경우, Entity의 Move함수를 사용해야 하나, Player 유도클래스의 Move로 오버라이딩 됨.
    ePtr->Move(1, 2);

    ePtr->PrintPosition();

    delete ePtr;



    return 0;
}