#include <iostream>

// 연산자 오버로딩 없이 함수로 구현된 예제임. (안좋은 예)

class Number {
private:
    int val;
public:
    Number(int val) : val{val} {}

    // 멤버함수 작동구현 1.
    Number Add(Number b) {
        return Number{val + b.val};
    }

    void Print() {
        std::cout << val << std::endl;
    }

    // 전역함수 사용을 위한 프로토타입. (내부구현해도 가능.)
    // 안하면 private 의 val 값 접근불가.
    friend Number Add(Number n1, Number n2);

};

class Player {
};


// 전역함수. 작동구현 2.
Number Add(Number n1, Number n2) {
    return Number{n1.val + n2.val};
}

int main() {
    Player p1;
    Player p2;

    // Player p3 = p1 + p2;     연산자 오버로딩 구현 안돼서 사용불가.

    // 기본 타입처럼 사용자 정의 타입을 연산자로 사용하고 싶을 때.
    int a = 1;
    int b = 2;
    int c = a + b;


    Number n1{5};
    Number n2{10};
    // Number n3 = n1 + n2;
    
    //작동구현 1. 멤버함수로 구현
    Number n3 = n1.Add(n2);
    n3.Print();

    //작동구현 2. 전역함수로 구현
    Number n4 = Add(n1, n2);
    n4.Print();


    // 코드가 직관적이지 않은 문제가 있음.
    // 연산자 오버로딩에도 제한사항이 좀 있음. (강의자료 ppt 11페이지 참고.)

    return 0;
}

