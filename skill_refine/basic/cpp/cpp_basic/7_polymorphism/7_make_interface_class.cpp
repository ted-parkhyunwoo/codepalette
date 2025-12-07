#include <iostream>


// 인터페이스 클래스는 관례상 I대문자를 적어줌
// 인터페이스 클래스는 추상클래스이며, 모든 멤버함수가 순수가상함수로 구현됨. 
// 유도클래스의 가이드라인 같은, 거의 겉 껍데기 같은 역할.
class IShape {

protected:
    int x;
    int y;

public:
    IShape(int init_x, int init_y): x(init_x), y(init_y) {};
    virtual void printPos() = 0;
    virtual void movePos(int dx, int dy) = 0;
    virtual ~IShape(){};
    virtual void printInfo() = 0;
};


class Player final : public IShape {
private:
    int* hp;
    int* xp;

public:
    Player(): IShape(0, 0) {
        this->hp = new int;
        this->xp = new int;
        *hp = 100;
        *xp = 0;
        std::cout << "Player Created." << std::endl;
    };

    virtual void printPos() override {
        std::cout << "pos: " << x << "," << y << std::endl;
    }

    virtual void movePos(int dx, int dy) override {
        x += dx;
        y += dy;
    }

    virtual void printInfo() override {
        printPos();
        std::cout << "status: hp= " << *hp << ", xp= " << *xp << std::endl;
    }

    // Player인스턴스 복제를 위한 복사생성자. Player의 생성자와 같이 이니셜라이저 리스트를 똑같이 작성해야함.
    Player(const Player& instance): IShape(instance.x, instance.y), hp(new int{*instance.hp}), xp(new int(*instance.xp)) {}

    // hp와 xp는 동적할당이므로 소멸자에서 해제 필수.
    virtual ~Player(){
        delete hp;
        delete xp;
    }

};


int main() {
    // 여러 활용.
    
    Player a;
    a.printPos();
    a.movePos(1,3);
    a.printPos();
    a.printInfo();


    IShape* b = new Player{};
    b->printPos();
    b->printInfo();
    delete b;
    b = &a;
    b->printInfo();
    b->printPos();

    Player c = a;
    c.printInfo();
    
    Player* d = new Player{};
    d->printInfo();
    delete d;

    return 0;
}
