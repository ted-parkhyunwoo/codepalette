#include <iostream>

int main() {

    // lambda - 익명함수 - 1회성으로 쓰기 유용함.
    // [capture](parameters) -> return_type { body }




    /* 캡처 절- 크게 값으로캡쳐, 참조로 캡쳐 두가지 - 해당 강의에는 일단 필요 없는 내용.
    [=] : 람다 내에서 사용되는 외부 변수를 모두 값으로 캡처
    [&] : 람다 내에서 사용되는 외부 변수를 모두 참조로 캡처
    [this] : 람다 내에서 클래스의 멤버 변수를 사용 가능하게 함
    [val] : 특정 변수만 값으로 캡처
    [&val] : 특정 변수만 참조로 캡처
    */
    // 메인함수 내에서도 함수를 단순 구현 가능.
    int val = 100;
    // 캡쳐 절에는 const로 선언되므로, 참조자를 안쓰면 값 변경 불가. 원본 손상을 원치 않는다면 참조자 대신 임시로 필요하면 deep-copy 해서 사용할 것.
    auto test = [&val](){std::cout << val * val << std::endl; val = val*val;};  
    test();
    std::cout << val << std::endl;



    // 램다 구현 단순 예제
    auto square = [](int x){std::cout << x*x << std::endl;};    // 램다를 정의하여 사용
    square(100);

    auto square2 = [](int x) -> int {return x*x;};              // 정수형을 반환하도록 램다를 정의하여 사용
    int result = square2(100);
    std::cout << result << std::endl;

    [](int x){std::cout << x*x << std::endl;}(100);             // 즉시사용

    int result2 = [](int x) -> int {return x*x;}(100);          // 정수형 반환형으로 램다를 즉시 사용하여 변수를 정의.
    std::cout << result2 << std::endl;

    return 0;
}