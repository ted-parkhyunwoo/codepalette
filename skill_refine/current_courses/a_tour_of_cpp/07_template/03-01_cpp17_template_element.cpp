#include <iostream>
#include <type_traits>
#include <any>


// cpp17 에서 T에게 숫자형 타입만 가능하게 할 경우

// 1.template에 enable_if 사용 : 컴파일타임에 에러발생시키는건 아래 방식과 동일.
//! 현업에서 보통 선호되는 방식임. cpp20에서 concept로 대체되는 추세.
template <typename T, typename std::enable_if<std::is_arithmetic<T>::value, int>::type = 0>
void printNumber(T num) {
    std::cout << "Number: " << num << std::endl;
}


// 2. static_assert를 사용하여 컴파일 타임에 에러 발생시킴 : 런타임에선 사용 안되니 주의(std::cout 처럼 타입을 직접 지정하여 캐스팅하면 사용 가능!)
//! 선호되는 방향은 아니나, 코드가 간결함.
template <typename T>
void printNumber2(T num) {
    static_assert(std::is_arithmetic<T>::value, "T must be a numeric type!");
    std::cout << "Number: " << num << std::endl;
}

int main() {
    printNumber(42);     // OK (int)
    printNumber(3.14);   // OK (double)
    // printNumber("hello");  // 컴파일 오류 (string 타입)
    
    std::any x = 42;
    // printNumber2(x);     // 마찬가지로 컴파일 오류.
    printNumber2(std::any_cast<int>(x));        //  static_cast 처럼 타입을 지정해주면 출력 가능!


    return 0;
}


