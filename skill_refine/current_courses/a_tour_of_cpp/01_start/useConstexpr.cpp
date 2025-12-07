#include <iostream>

constexpr int square(int a) {
    return a * a;
}

// const는 런타임에 평가, constexpr 은 컴파일타임에 평가를 함(속도면에서 우위, 대신 런타임에선 사용불가.)
int main() {
    const int A{square(3)};
    constexpr int B{square(3)};        //! constexpr 에 초기화시 함수 사용하려면 함수도 constexpr를 사용해야함.
    std::cout << A << " " << B << std::endl;

    return 0;
}