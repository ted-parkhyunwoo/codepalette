#include <iostream>
#define MAX(a, b) (a > b? a : b)

// pre-processor(전처리기) 를 활용한 제네릭 프로그래밍. (대신 template를 쓰자..)
//! 단점: 디버깅 불가. namespace 안돼서 전역범위로만 사용가능.

int main() {
    int a = 3;
    int b = 5;
    std::cout << MAX(a, b) << std::endl;    // MAX(a, b) 의 코드를 (3 > 5? 3 : 5) 로 그냥 "복사, 붙여넣기" 해주는 매크로 전처리기.
    //! 곱셈 나눗셈등 순서가 바뀔 수 있으니 전처리기 매크로는 항상 괄호를 감싸서 사용하도록 한다.
    double c = 3.14;
    double d = 1.592;
    std::cout << MAX(c, d) << std::endl;

    return 0;
}