#include <iostream>
/* 활용 예제. - 복잡하면 메인함수만 봐도 무방함.(virtual. override만 적절히 사용한다면.)
for문 하나로 모두 move함수를 다르게 작동하게 사용가능.
예를들어 플레이어는 *3, 보스는 *2, 나머지는 *1로. 
*/


class Entity {
public:
    Entity(int x, int y) : x(x), y(y) {}
    virtual ~Entity() {}  // Virtual destructor
    virtual void Move(int dx, int dy) {
        x += dx;
        y += dy;
        std::cout << "Entity moved to (" << x << ", " << y << ")\n";
    }
protected:
    int x, y;
};

class Player : public Entity {
public:
    Player(int x, int y, int level) : Entity(x, y), level(level) {}
    virtual ~Player() {}  // Virtual destructor
    void Move(int dx, int dy) override {
        x += dx*3;
        y += dy*3;
        std::cout << "Player moved to (" << x << ", " << y << ")\n";
    }
private:
    int level;
};

class Enemy : public Entity {
public:
    Enemy(int x, int y, int strength) : Entity(x, y), strength(strength) {}
    virtual ~Enemy() {}  // Virtual destructor
    void Move(int dx, int dy) override {
        x += dx;
        y += dy;
        std::cout << "Enemy moved to (" << x << ", " << y << ")\n";
    }
private:
    int strength;
};

class Boss : public Enemy {
public:
    Boss(int x, int y, int strength, int power) : Enemy(x, y, strength), power(power) {}
    virtual ~Boss() {}  // Virtual destructor
    void Move(int dx, int dy) override {
        x += dx*2;
        y += dy*2;
        std::cout << "Boss moved to (" << x << ", " << y << ")\n";
    }
private:
    int power;
};

int main() {
    // 포인터 형태.
    Entity *p1 = new Entity{0, 0};
    Entity *p2 = new Player{0, 0, 2};
    Entity *p3 = new Enemy{0, 0, 2};
    Entity *p4 = new Boss{0, 0, 2, 5};

    Entity *array[] = {p1, p2, p3, p4};

    for (int i = 0; i < 4; i++) {
        array[i]->Move(1, 1);
    }

    // 동적할당 해제.
    for (int i = 0; i < 4; i++) {
        delete array[i];
    }

    // 참조자 형태.
    Player p{0,0,1};
    Entity& ref = p;
    ref.Move(1,1);

    return 0;
}
