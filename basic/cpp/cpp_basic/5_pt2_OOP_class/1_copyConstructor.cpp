//객체가 복사될 때 실행. 
// 1. passByValue로 매개변수 전달시 : func(int a) 에 int* , iunt& 도 아닌경우. 호출스택에 복사된다는것을 상기.
// 2. 함수가 value의 형태로 결과 반환시 : return a; 함수호출스택에서 메인함수로 a를 복사해오는 것을 상기.
// 3. 기존객체 기반으로 새로운 객체 생성시. - 정의된 클래스의 객체복사는 좀 다른게, 어떻게 복사되어야 할지 정의를 해주어야함. - 생성자처럼 마찬가지로 복사생성자도 자동으로 기본 복사 생성자를 정의하나, 제 역할은 힘들어서 정의해줘야함.


//사용 이유 1: 멤버변수에 포인터 존재시 복사과정에 문제 발생할 수 있음.->deep copy 사용한 복사생성자 사용.
//! 2: 복사비용에 대한 인식(클래스는 많은 데이터를 포함할 수 있음을 상기)

#include <iostream>


struct Player {
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


    return 0;
}
