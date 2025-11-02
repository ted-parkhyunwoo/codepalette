#include <iostream>

void static_local_increment() {
    static int num = 1; 
    // 한정적으로 예외변수 사용 가능
    //! static으로 선언된건 함수가 종료 되어도 지역변수가 아니라 전역변수 처럼 작동하는 듯
    std::cout <<"num : " << num << std::endl;
    num++;
    std::cout <<"num : " << num << std::endl;
}


int main() {

    static_local_increment();
    static_local_increment();
    static_local_increment();

    return 0;
}