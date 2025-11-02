// public 어디서든.
// private 클래스멤버,friend클래스만 가능
// protected 상속클래스 객체에서만 접근가능

#include <iostream>


class Player {
    public:
        std::string name;
        int health;
        int getHealth();    //클래스 외부구현용 프로토타입 선언
        void xpup() {
            xp += 100;
        }
        void xpprint() {
            std::cout << xp;
        }
    private:
    //private는 직접 접근이 안됨.  -정보은닉.
    // 보통 멤버함수로 논리구현을 위해 private를 씀 (계좌 0 이하시 송금불가, 체력 100이상은 설정 못하게 하기 위해 등등).  
        int xp;
};
// 클래스선언의 메서드 외부구현. 내부구현의 멤버 함수인건 똑같음.
int Player::getHealth(){
    return health;
}

int main() {
    Player p;
    p.health = 10;

    Player* ptr = new Player();
    (*ptr).health = 30;
    ptr->name = "김상철";

    //private 접근시 이런식으로 사용함.
    ptr->xpup();
    ptr->xpprint();
    delete ptr;

    return 0;
}