#include <iostream>

void sayHello();
// 컴파일시 g++ main.cpp sayHello.cpp 연속으로 입력하면 여러 소스파일을 사용하여 컴파일. (c++20 에서는 헤더로 넣는 방법도 존재함.)
int main()
{
    sayHello(); 


    return 0;
}