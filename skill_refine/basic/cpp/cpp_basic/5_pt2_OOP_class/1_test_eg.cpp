#include <iostream>

class Player {
public:

Player(std::string name="none", int hp=100, int xp=0) : name(name), hp(hp), xp(xp) {
    std::cout << name << " user created." << std::endl;
}


void showInfo() {
    std::cout << name << std::endl << hp << std::endl << xp << std::endl;
}

private:
std::string name;
int hp;
int xp;

};


int main() {
    Player a("ted");
    a.showInfo();

    // 3의 예로 복사생성 두가지. (변수에 포인터타입이 없어서 기본 복사생성자도 정상작동.)
    Player b = a;
    Player d {a};

    //! 이건 복사생성이 아님. (나중에 배울 대입연산의 개념.) none이 먼저 생성되고 대입.
    Player c;
    c = a;

    std::string username = "kimCopy";
    std::string* ptrName = &username;
    Player e(*ptrName);
    e.showInfo();


    Player f {e};
    f.showInfo();



    return 0;
}
