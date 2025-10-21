#include <iostream>

class Point
{
    private:
    int x;
    int y;

    public:
    Point(int a, int b) {
        // this는 현재 메모리의 주소값 - 포인터 처럼 ->로 값을 넣을 수 있다.
        // 멤버 이니셜라이저 리스트나 기본매개변수 대신 이렇게 값을 넣을 수도 있음.
        //! 만약 a, b 대신 x, y 라는 매개변수 이름을 사용시 x {x} 라는 식의 명확하지 않은 방식을 this로 지정할 수 있게 됨.
        this->x = a;
        this->y = b;
        std::cout << x << " " << y << std::endl;

    }

};



int main() {

    Point p{2,3};
    return 0;
}