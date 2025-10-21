#include <iostream>

int main(void) {
    // 컴파일, 링킹 오류는 잡기 쉬우나 런타임,논리 오류는 디버깅으로 잡아야함.
    //! 중단점은 실행하기 직전상태. 
    // f5로 디버깅 시작.
    // f10으로 한줄씩 단계실행
    // f11으로 함수 안으로 들어감(안에선 f10으로 한줄 씩 실행.)
    
    int a = 10;
    int b = 20;
    int result = 0;
    result = (a > b) ? (a++) : (b--);

    return 0;
}