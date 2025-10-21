#include <stdio.h>
#include <stdlib.h>


// 독립된 기억공간을 가지는 구조체.
struct Test1 {
    int a1;
    short a2;
    char a3;
};

// 같은 메모리공간을 공유하는 공용체.
union Test2 {
    int a1;
    short a2;
    char a3;
};


int main(int argc, char* argv[]) {

    struct Test1 t1;
    t1.a1 = 65535;

    printf("t1.a1 : %d\n", t1.a1);
    printf("t1.a2 : %d\n", t1.a2);  // dummy
    printf("t1.a3 : %d\n", t1.a3);  // dummy
    
    //! 공용체: 모든 멤버가 같은 메모리 공간을 공유함. 가장 큰 자료형 크기만큼만 메모리 할당. 한 번에 하나의 멤버만 올바른 값으로 사용 가능.
    union Test2 t2;
    t2.a1 = 2147483647; // 4바이트(32bit) signed 최고 숫자.

    // 11111111 11111111 11111111 11111111 -> 65535
    printf("t2.a1 : %d\n", t2.a1);  
    printf("t2.a2 : %d\n", t2.a2);
    printf("t2.a3 : %d\n", t2.a3);


    t2.a2 = 20;
    printf("t2.a1 : %d\n", t2.a1);  // a2를 쓰면 a1의 값이 일부 덮여서 원래 값이 보장되지 않음

    // 따라서 굳이 사용한다면 다시 초기화.(멤버를 다시 초기화해도, 이전에 저장된 값(a1 등)은 완전히 보장되지 않으므로 신뢰할 수 없음; 할당한 공간에 다른 코드들의 메모리접근은 허용되진 않지만, 확실히 보장되는 정보는 아니라고 보는것이 합당.)
    t2.a1 = 0;
    t2.a2 = 20;
    printf("t2.a1 : %d\n", t2.a1); 
    printf("t2.a2 : %d\n", t2.a2);
    printf("t2.a3 : %d\n", t2.a3);
    return 0;
}