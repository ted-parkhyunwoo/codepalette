#include <iostream>


class Point {
private:
    int xpos;
    int ypos;
public:
    Point(int x = 0, int y = 0) : xpos(x), ypos(y) {}

    void ShowPosition() {
        std::cout << "[" << xpos << "," << ypos << "]" << std::endl;
    }


    /* 복습내용-
    const 참조자 = 복사비용 절약.
    const 사용시 객체들의 값 변경을 미연 방지.
    추가로 그럴일은 많이 없지만 만약 p3 =  p1 + p2 로 사용했는데, p1, p2 의 값을 0으로 만드는 구현등이 필요하다면 const를 안써도 됨. 

    멤버함수의 매개변수const와 const키워드
    앞의 const는 매개변수 Point참조자 p의 값을 바꾸지 않는다는 뜻. (매개변수가 const)
    뒤의 const는 현재 객체의 값을 바꾸지 않는다는 뜻.(멤버함수가 const)
    */

    // 이항연산 오버로딩
    Point operator+(const Point& p) const {
        return Point(xpos + p.xpos, ypos + p.ypos);
    }

    Point operator+(int value) const {
        return Point(xpos + value, ypos + value);
    }
    
    Point operator-(const Point& p) const {
        return Point(xpos - p.xpos, ypos - p.ypos);
    }

    // 단항연산 오버로딩. -. ++, ! 등.
    Point operator-() const {
        return Point(-xpos, -ypos);
    }
    // 현재 조건은 !를 적용할 것이 없으니 그냥 음수인지 확인.
    bool operator!() const {
        return (xpos >= 0 && ypos >= 0);
    }
    // ++객체, 객체++는 선행연산, 후행연산으로 구분되는 단항연산자. 각자의 차이는 3번문서 참고.
    //간단요약 = 멤버변수 ++ 연산하되, 연산전에 더미 객체 복사생성후 리턴 vs 멤버변수 ++ 연산 후 리턴.



    bool operator==(const Point& p) const {
        return xpos == p.xpos && ypos == p.ypos;
    }

    // 전역멤버함수를 구현하기 위해 friend.
    friend Point operator+(int value, Point& obj);

};

Point operator+(int value, Point& obj) {
    return Point(value + obj.xpos, value + obj.ypos);
}

int main() {

    // 이항연산자 오버로딩.
    Point p1{3,5};
    Point p2{3,5};
    p1.ShowPosition();

    Point p3 = p1+p2;
    // + 를 사용하면 컴파일러가 p1.operater+() 함수를 실행하는것으로 해석함.
    p3.ShowPosition();


    // == 사용시 p1.operator==() 함수를 호출.
    if (p1 == p2) {
        std::cout << "Same" << std::endl;
    } else {
        std::cout << "Different" << std::endl;
    }

    // 단항연산자 오버로딩
    Point p4{5,1};
    p4.ShowPosition();
    std::cout << !p4 << std::endl;
    p4 = -p4;
    p4.ShowPosition();

    std::cout << !p4 << std::endl;

    // 이항연산의 멤버함수 구현시 문제 해결 -> 전역함수로 오버로딩 (4번 코드 로 참고.)
    const Point p7{ -3, -3};
    Point p8 = -p7;
    p8.ShowPosition();
    p8 = p8 + 3;                //p8.operator+(3);
    p8.ShowPosition();
    // p8 = 2 + p8;             //3.operator+(p8);
    // p8.ShowPosition();       //이렇게 해석불가. 이럴 경우 멤버함수로 연산자 오버로딩 하지 않고, 전역함수로 해야함.


    return 0;
}