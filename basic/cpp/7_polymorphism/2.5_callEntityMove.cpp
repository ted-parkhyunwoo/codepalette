#include <iostream>



class Entity {
protected:
    int x;
    int y;
public:
    Entity(int x, int y) : x(x), y(y) {}

    virtual void Move(int dx, int dy) {
        // 기본 클래스의 Move 함수
        x += dx;
        y += dy;
    }

    void PrintPosition() {
        std::cout << x << "," << y << std::endl;
    }

    virtual ~Entity() {}
};

class Player : public Entity {
private:
    int hp;
    int xp;
    bool useBaseMove;
public:
    Player(int x, int y, int hp, int xp, bool useBaseMove = false) 
        : Entity(x, y), hp{hp}, xp{xp}, useBaseMove{useBaseMove} {}

    void SetUseBaseMove(bool value) {
        useBaseMove = value;
    }

    void Move(int dx, int dy) override {
        if (useBaseMove) {
            Entity::Move(dx, dy);  // 기본 클래스의 Move 함수 호출
        } else {
            x += dx * 2;  // 파생 클래스의 Move 로직
            y += dy * 2;
        }
    }

    ~Player() override {}
};

int main() {
    Player* p = new Player{1, 1, 10, 10};

    p->Move(1, 2);  // 파생 클래스의 Move 로직 수행
    p->PrintPosition(); // 출력: 3,5

    p->SetUseBaseMove(true);  // 기본 클래스의 Move 함수 사용 설정
    p->Move(1, 2);
    p->PrintPosition(); // 출력: 4,7

    p->SetUseBaseMove(false);  // 파생 클래스의 Move 로직 사용 설정
    p->Move(1, 2);
    p->PrintPosition(); // 출력: 6,11

    delete p;

    return 0;
}
