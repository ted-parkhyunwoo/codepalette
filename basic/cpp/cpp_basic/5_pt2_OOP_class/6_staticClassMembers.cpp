#include <iostream>

//! class의 static. 멤버 함수와 변수를 static으로 설정하면, 객체별로가 아니고, 모든 객체들이 같은 멤버함수와 멤버 변수를 공유함.

//static은 stack이나 heap에 저장되지 않음. 별도의 static 메모리에 저장.
//[코드공간] [static 변수, 전역변수,string 리터럴], [stack], [heap] 2번째에 저장.

class Player
{
    private:

    int x, y;
    int speed;
    static int numPlayer;   //!선언만 되고, 클래스에선 초기화 불가능. 전역에서 변경해야함.

    public:

    Player(int x, int y, int speed) : x{x}, y{y}, speed{speed}
    {
        std::cout << this << std::endl;
        numPlayer++;
    }

    void SetPosition(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void PrintPosition() 
    {
        std::cout << x << "," << y << std::endl;
    }
    static void getNumPlayer() {    //! 전역 멤버함수.
        std::cout << "All Player : " << numPlayer << std::endl;
    }

};

int Player::numPlayer = 0;  //! 이렇게 초기화는 전역에서 해야함.

int main() {
    
    Player p{1, 1, 1}; 
    Player a{1, 1, 1};
    Player d{a};

    Player::getNumPlayer(); // static 멤버 함수 호출
    // p.getNumPlayer();   //둘 다 작동함.

    return 0;
}

