#include <iostream>

class Test {
private:
    int a;

public:
    // 생성자
    Test(int value) : a(value) {}

    // 선행 연산자 ++ 오버로딩 (prefix)
    // 복사비용 아끼기 위해 참조자 사용.(참조자 사용 안하면 매 사용시 객체 새로생성됨)
    Test& operator++() {
        ++a; // 값을 증가시킨 후
        return *this; // 변경된 객체를 반환
    }

    // 후행 연산자 ++ 오버로딩 (postfix)
    // 컴파일러가 후행연산자 라고 식별할수 있도록 더미로 의미없지만 int를 넣어줌. (안하면 선행연산으로 생각함. 객체++ 를 컴파일러가 인지하게 하기위해.)
    Test operator++(int) {
        Test temp = *this; // 현재 상태를 저장
        a++; // 값을 증가시킨 후
        return temp; // 저장된 이전 상태를 반환
    }

    // 값을 출력하기 위한 함수
    void print() const {
        std::cout << "a: " << a << std::endl;
    }
};

int main() {
    Test obj(5);

    std::cout << "Initial value: ";
    obj.print();

    ++obj; // 선행 연산자
    std::cout << "After prefix ++: ";
    obj.print();

    obj++; // 후행 연산자
    std::cout << "After postfix ++: ";
    obj.print();

    return 0;
}
