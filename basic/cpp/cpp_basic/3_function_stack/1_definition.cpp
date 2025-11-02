/* 함수는 기능, 필요한 정보,리턴값,오류,성능제약 등만 알면 됐지, 내부동작 메커니즘을 이해할 필요가 없다.    - 큰 프로젝트 작성시 리턴값, 이름과 매개변수, 기능설명만 적어놓으면 좋다
*/

#include <iostream>

void print_hello(); //prototype. 컴파일러에 미리 알림.
//! 컴파일 할 때 함수의 위치가 위에 있도록 하거나(작은규모), 프로토타입으로 알려야함(큰규모시.).

int main() {

    print_hello();  //함수명은 이름만 봐도 역할을 알 수 있도록.

    return 0;
}

void print_hello() {        // 리턴값이 없으면 void.
    std::cout << "Hello" << std::endl;
} 

