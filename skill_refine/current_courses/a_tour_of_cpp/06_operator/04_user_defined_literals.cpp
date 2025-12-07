#include <iostream>

// 매개변수로는 특정 타입들만 사용 가능함.
// 리턴 타입 명시 필요.
// operator""리터럴 형식을 따름. (관례는 _m 이런식으로 씀: 표준접미사 f,u,l 등 충돌방지)
// 컴파일타임에 평가되도록 constexpr로 정의하는게 일반적.
constexpr int operator"" _m(unsigned long long m) {
    return static_cast<int>(m);
}

int main() {
    int a = 30_m; // 사용자 정의 리터럴 사용
    std::cout << a << std::endl;

    return 0;
}