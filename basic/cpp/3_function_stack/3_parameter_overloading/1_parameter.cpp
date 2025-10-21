#include <iostream>


int add_numbers(int a, int b=200);  //!인자 선언시 기본 인수를 넣을 수 있음. (오른쪽부터 선언해야함.)
// 인수(argument) 를 2개의 정수로 받기 위해 정수형 인자(parameter) 두개 정의.
// 프로토타입, 함수의 정의, 함수의 호출에서도 같은 방식으로 해야함.

int main() {

    int result = add_numbers(100); //파이썬과 다르게 a=100 이런거 지원안됨. 순서를 명확히 할 것.
    std::cout << result;
    
    return 0;
}

int add_numbers(int a, int b) {     //! 기본인수는 프로토타입에만 쓰거나, 프로토타입이 없는 경우는 메인함수 위에 선언된 함수에 넣을 수 있음. -둘다는 안됨.

    return a+b;
}
 