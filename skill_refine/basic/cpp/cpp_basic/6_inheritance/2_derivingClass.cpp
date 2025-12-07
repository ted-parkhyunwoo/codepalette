#include <iostream>


// 상속 기초 문법 (유도클래스, 자녀클래스)

class Entity {
    //부모클래스 (베이스, 이름은 당연히 아무거나 사용해도 됨.)


// 접근제한자. private: 은 Entity 내부에서만 가능하나, protected를 하면 상속클래스까지 사용 가능. 
protected:
    int x;
    int y;
public:

    Entity(int x, int y) : x{x}, y{y} {}    //생성자.

    void ShowPosition() //위치 출력 멤버함수
    {
        std::cout << "[" << x << ", " << y << "]" << std::endl;
    }

    void Talk()
    {
        std::cout << "Hello." << std::endl;
    }

};

class Player : public Entity {

private:
    int hp;
    int xp;
    int speed;
public:
    Player(int x, int y, int speed)
    : Entity {x, y} {
        this->speed = speed;
        hp = 100;
        xp = 100;
    }
    void Move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

};

// access-specifier (: 뒤에, Base 앞에) 에는 public, private, protected 등이 있음.
//! 하지만 public 외에는 잘 사용하지 않음.  java, C#에는 아얘 없을 정도로 인기 없음.

int main() {

    Entity e{1, 1};
    e.ShowPosition();
    e.Talk();

    Player p{5, 5, 10};
    p.Talk();
    p.ShowPosition();


    return 0;
}