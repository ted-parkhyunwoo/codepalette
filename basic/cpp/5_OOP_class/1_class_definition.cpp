#include <iostream>

// Class 정의
class Player {
    //멤버변수,데이터 attributes
    std::string name;
    int health;
    int xp;

    //멤버함수,행위 method
    void Talk(std::string text);
    bool IsDead();
};


int main() {

    // 객체(오브젝트) 생성
    Player p;

    // 당연히 클래스도 동적메모리 할당 가능.
    Player* p2 = new Player();
    delete p2;

    return 0;
}