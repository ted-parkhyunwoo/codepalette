#include <stdio.h>
#include <stdlib.h>

int A = 1;

void func() {
    // 다른 scope영역에선 사용할 수 없음.
    int A = 5;
}

int main(int argc, char* argv[]) {
    // 전역변수 사용.
    A--;
    printf("%d\n", A);


    int A = 2;

    // 전역/지역 이름이 같다면 지역변수를 사용함.
    printf("%d\n", A);    
    return 0;
}