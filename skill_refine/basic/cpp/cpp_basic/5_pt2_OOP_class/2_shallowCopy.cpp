#include <iostream>

class Player {
public:
    Player(int hp, int xp) : hp{hp}, xp{xp} {
        std::cout << "constructor created." << std::endl;
    }

    // 복사생성자. 이론상 멤버 초기화 리스트를 넣어야하나, 실수로 안넣어도 일부 컴파일러는 처리함. -- 넣는게 맞음.
    //! const는 복사하면서 값을 변경하지 않겠다는 약속과 같음.- 실제 복사생성자 내부에 값 변경이 없다 하더라도 넣는게 관습.
    //! 참조자는 당연히 호출스택에 value를 카피하지 않고 직접 다루겠다는 의미.(메모리 자원절약)
    Player(const Player& other) : hp{other.hp}, xp{other.xp} {      //const Class명, 참조자& data 식으로 선언됨.
        std::cout << "copy constructor created." << std::endl;
    }

    void Print(){
        std::cout << hp << " " << xp << std::endl;
    }

private:
    int hp;
    int xp;
};

// 함수 호출시 해당 함수 호출스택에 밸류가 복사됨.
void PrintInformation(Player p) {
    p.Print();
}

int main() {
    Player p(10, 2);

    // p.Print(); // 복사생성자가 호출 안됨.(정확히는 컴파일러가 만든 것이 있긴 하나, 실행 안됨.)
    PrintInformation(p);  // 이 경우는 커스텀으로 작성한 복사생성자 호출됨.
    // 커스텀 한것이 없더라도 컴파일러가 만든 기본 복사 생성자가 호출 되는건 명확함.

    return 0;
}