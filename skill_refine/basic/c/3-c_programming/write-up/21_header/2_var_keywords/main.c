#include <stdio.h>
#include <stdlib.h>
#include "./test1.h"

//! 컴파일 방법: gcc main.c test1.c -Wall -Wextra -o main.exe
// 간단하게 gcc main.c test1.c  

// 아래 main함수의 extern의 내용을 참고하여 다음 extern 선언을 이해할 것.
extern int global_a;
extern int global_b;

int main(int argc, char* argv[]) {
    
    /*
    auto    자동소멸 지역변수. 생략가능
    extern  프로그램이 끝날때 까지 사용되는 변수. 생략가능
    register    변수접근 빨라야 할 경우 사용.
    static      전역변수로 지정: 함수가 끝나도 유지됨.
    */

    // 일부 c에선 auto로 지정하지 않으면 변수지정에 오류가 나는 경우도 있음.
    auto int local_a1 = 100;
    auto int local_a2 = 200;

    printf("local_a1: %d\n", local_a1);
    printf("local_a2: %d\n", local_a2);

    test1();

    // 레지스터 공간에 할당. 자주사용하는 변수에 지정가능(많이 생성하면 안됨.)
    //! 컴파일러가 고지능화 되면서 이젠 거의 자동으로 되며, cpp++17에선 경고, c++20에선 사라짐.
    //! C의 경우에도 비슷하나, 참조자/역참조를 쓸 수 없고 실효성이 거의 사라짐
    register int i;
    for (i = 0; i < 10; i++) {
        printf("i: %d\n", i);
    }


    // static에 관한 내용은 test1.c의 test2()함수 참고.
    test2();
    test2();
    test2();

    // extern에 관한 내용. test3() 과 global_a 등 참고.
    test3();    // 함수로는 실행에 문제가 없음.

    // 상속된 파일의 변수를 그냥 쓰면 오류발생. extern 선언 해야함
    printf("global_a: %d\n", global_a);
    printf("global_b: %d\n", global_b);    

    return 0;
}