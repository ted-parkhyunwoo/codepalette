#include <iostream>

// inline함수는 함수 호출 스택을 쌓지 않고, 메인함수의 호출스택에서 똑같은 기능을 바로 처리.
// 호출이 빠르지만, 바이너리 파일의 용량이 커질 수 있음.
// 때때로 컴파일러에서 알아서 처리하기도 함-너무 간단하면 코드를 바꾸기도 한단뜻.

inline int add_numbers(int a, int b) {
    return a+b;
}

int main() {

    int result = add_numbers(100,200); // 이부분에서 합연산 바로 한단 뜻.
    std::cout << result;

    return 0;
}

//! 추가첨언 - 함수는 모든 변수를 복사생성 하기 때문에, inline 함수가 자원절약에 도움될 수 있으나 앞서 설명했듯이 바이너리 용량이 커질 수 있음에 주의.
