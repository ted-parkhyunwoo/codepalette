#include <stdio.h>
#include <stdlib.h>

// 메모리공간을 효율적으로 사용하기 위한 비트필드.

struct Test1 {
    unsigned int a1;
    unsigned int a2;
};

struct Test2{
    unsigned int a1:1;      // 비트 수. 1비트 사용.
    unsigned int a2:1;
};

int main(int argc, char* argv[]) {
    
    struct Test1 t1;
    struct Test2 t2;

    printf("t1 : %d\n", sizeof(t1));
    //! sizeof 는 바이트를 가져오기때문에 사실은 2비트만 사용.
    //! 새로 알게된 중요 포인트: 사실은 논리비트며, 실질적 물리공간은 2비트가 아님.
    printf("t2 : %d\n", sizeof(t2));

    t1.a1 = 1;
    t2.a1 = 1;

    printf("t1.a1 : %d\n", t1.a1);
    printf("t2.a1 : %d\n", t2.a1);

    //!중요.
    t1.a2 = 2;      // 1 0
    t2.a2 = 2;      // 1 0  중 자릿수 때문에 앞에는 버림처리 되고 0만 들어가버림.

    printf("t1.a2 : %d\n", t1.a2);
    printf("t2.a2 : %d\n", t2.a2);    

    return 0;
}