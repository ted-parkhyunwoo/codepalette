#include <iostream>

int main() {
    int a = 0;  //일반적인 변수도 이렇게 선언해 주는게 좋은 것 처럼

    int* b;     //int* 까지가 타입이라고 생각.
    double* c = nullptr;    //위 보다는 여기까지 해주는게 좋음. 포인터는 널이 아니면 문제를 일으킴.

    b = &a;     // 포인터에는 주소값을 넣어야됨. &를 넣으면 주소값 반환.

    // b = &10; // 당연히 이런식으로 쓸 순 없음. 에러메세지에 lvalue(주소값얻을수있음), rvalue 로 구분됨.


    // nullptr을 쓸 때와 안쓸 때 출력 비교. 64비트 포인터는 8바이트.(32=4바이트)
    int* x;
    std::cout << x << std::endl;
    std::cout << sizeof(x) << std::endl;
    int* y = nullptr;
    std::cout << y << std::endl;
    std::cout << sizeof(y) << std::endl;


    return 0;
}