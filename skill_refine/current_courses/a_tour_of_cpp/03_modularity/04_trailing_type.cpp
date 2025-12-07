#include <iostream>

int main () {

    // auto 가 종종 문제를 일으키는 것을 피하고싶거나 람다등을 사용할 때 반환타입을 명시할 수 있다.
    // std::function<double(int)> 이게 원래 아래코드의 auto의 역할임. 람다는 타입명시가 복잡하므로 auto로 하고 반환타입을 double 지정.
    auto myFunc = [](int a) -> double { return a / 2.0; };
    std::cout << myFunc(5) << std::endl;
    return 0;
}