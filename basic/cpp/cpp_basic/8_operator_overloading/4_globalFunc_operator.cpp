#include <iostream>

// 멤버함수로 연산자 오버로딩시 객체 + 3은 되는데, 3 + 객체 등이 사용불가한 문제.
// 예 : (int)3.operator+(객체) 라는 것을 컴파일러가 이해 불가. 3.operator 자체가 진행 안되기 때문.
// 해결 :
// 전역함수와 멤버함수 두가지로 구현하면 컴파일러가 알아서 오버로딩 함.


class Point {
private:
    int xpos, ypos;
    
public:

    Point(int x = 0, int y = 0) : xpos(x), ypos(y) {}

    Point operator+(int value) const {
        return Point(value + xpos, value + ypos);
    }

    // 비멤버 함수이므로, 멤버함수 키워드 const사용 불가(매개변수는 가능).
    //! 중요. friend 로 프로토타입 작성하고 전역에 구현해도 되지만, 여기서 내부구현 해도 가능. (그렇다고 멤버함수는 아님.)
    // friend 로 프로토타입 구현 안할 시 - 객체 private변수 접근불가.
    friend Point operator+(int value, const Point& obj);
    /* 내부 구현된 전역함수의 예. (기능상 동일.)
    friend Point operator+(int value, const Point& obj) {
        return Point(value + obj.xpos, value + obj.ypos);
    }
    */

    // const 정의된 객체도 사용가능하기 위해 const 키워드 사용
    void ShowPos() const {
        std::cout << "[" << xpos << "," << ypos << "]" << std::endl;
    }

    // 객체 + 객체 구현
    Point operator+(const Point& lObj) const {
        return Point(xpos + lObj.xpos, ypos + lObj.ypos);
    }
};


// 전역함수로 연산자오버로딩.  -주의 Point::operator 아님
//! 이런식으로 작성하면 컴파일러가 알아서 두가지 케이스를 구분함. (정수 + 객체, 객체 + 정수)
//! 객체.operator+(p1, p2) 를 먼저 찾고, 다음 찾는게 operator+(p1, p2)
Point operator+(int value, const Point& obj) {
    return Point(value + obj.xpos, value + obj.ypos);
}

int main() {
    Point p(1, 2);

    // 멤버함수로 연산자 오버로딩
    const Point result = p + 5;  // result.operator+(5)
    result.ShowPos();

    // 비멤버함수(전역함수)로 연산자 오버로딩
    const Point result2 = 5 + p;  // operator+(5, p)
    result2.ShowPos();


    // 객체 + 객체
    const Point ojbTest = Point(1,2) + Point(3,4);
    // Point(1,2).operator+(Point(3,4));
    ojbTest.ShowPos();

    return 0;
}
