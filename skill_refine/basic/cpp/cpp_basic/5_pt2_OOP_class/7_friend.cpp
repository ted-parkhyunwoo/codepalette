#include <iostream>

//! friend는 감춰진 private를 필요할 때만 열어주는 것이기 때문에, 완전한 정보은닉이 안될 수 있으니, 필요할 때만! 사용 할 것.

class Player
{
    friend void DisplayPlayer(const Player& source);
    //! 아래 함수에서 쓰일 friend를 프로토타입처럼 선언. (비슷해보여도 멤버함수가 아님.)

    //! 마찬가지로, 이렇게 클래스도 friend 지정 가능.
    friend class Game;

    private:

    int x, y;
    int speed;

    public:

    Player(int x, int y, int speed) : x{x}, y{y}, speed{speed}
    {
        std::cout << this << std::endl;
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

    int getXpos() const {
        return x;
    }
    int getYpos() const {
        return y;
    }

};

// 멤버함수가 아님. friend 없이 하려면 이렇게 사용해도 되지만,
// void DisplayPlayer(const Player& source) {
//     std::cout << source.getXpos() << "," << source.getYpos() << std::endl;
//     //friend가 아니면, private에 접근 불가.
// }

//! 이렇게 쓰면 접근 가능.
void DisplayPlayer(const Player& source) {
    std::cout << source.x << "," << source.y << std::endl;
    //friend가 아니면, private에 접근 불가.
}

//! Player 가 맺은 friend 의 Game클래스.
class Game
{

};


int main() {
    Player p1{1, 1, 1}; 
    DisplayPlayer(p1);
    //Player::DisplayPlayer() 가 아님.
    return 0;
}

