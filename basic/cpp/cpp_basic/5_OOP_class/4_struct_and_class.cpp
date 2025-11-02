#include <iostream>

// Class
//! 관습- class는 private기본으로, 멤버함수로 데이터 (멤버변수)접근하는 방향.
class Player {
public:
    void Talk(std::string text);
    bool IsDead();
private:
    std::string name;
    int health;
    int xp;

};

//! struct 에. C++에선 함수도 넣을 수 있으므로, 구조체와 클래스는 같다. 
//(기본이 private냐 public이냐 차이. 구조체는 public 기본.)
//! 관습 - 간단한 public 멤버변수,데이터는 struct 사용. 

struct Player2 {
    std::string name;
    void PrintHealth(){
        std::cout << health << std::endl;
    }
private:
    int health = 100;
};

int main() {

    Player p;

    // 구조체 테스트.
    Player2 test_struct;
    test_struct.PrintHealth();

    return 0;
}