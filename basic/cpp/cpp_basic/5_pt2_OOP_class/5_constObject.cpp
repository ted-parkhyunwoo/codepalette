#include <iostream>

//! const로 Player 객체를 생성한 후, 멤버 변수 값을 바꾸지 않을 때는 사용 할 멤버함수도 const라고 명시 해주어야 한다는 내용.

class Player
{
    private:

    int x, y;
    int speed;

    public:

    Player(int x, int y, int speed) : x{x}, y{y}, speed{speed}
    {
        std::cout << this << std::endl;
    }

    void SetPosition(int x, int y) //const //! 이렇게 값 바꾸는데, const라고 구라쳐도 여기서 에러뜸.
    {
        this->x = x;
        this->y = y;
    }
    void PrintPosition() //const  //! const를 뒤에 적어서 값을 바꾸지 않는다는 것을 컴파일러에 알려야 함.
    {
        std::cout << x << "," << y << std::endl;
    }

};


int main() {
    const Player p{1, 1, 1}; //! const 지정했으니, SetPosition 사용시 에러!
    // p.SetPosition(2, 2);
    p.PrintPosition();    //! 그냥 쓰면 PrintPosition은 값을 바꾸지 않는데도 사용시 에러가 남.

    return 0;
}

