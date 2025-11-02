// C++20 에서만 사용 가능한 코드이므로, c_cpp_properties.json, tasks.json 설정이 적절한지 시험해 볼 수 있다.
// 내 환경에선 ctrl+f1 는 c++17을 이용하기 때문에, 직접 우측상단 c/c++파일 실행 혹은 디버그로 진행한다.

#include <concepts>
#include <iostream>

// Concept 정의: Arithmetic 타입인지 검사
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

// Arithmetic 타입만 허용하는 함수
template<Arithmetic T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(3, 5) << std::endl;          // 정수 연산
    std::cout << add(3.5, 2.5) << std::endl;      // 실수 연산
    // std::cout << add("Hello", "World");       // 컴파일 오류 (Arithmetic이 아님)

    return 0;
}