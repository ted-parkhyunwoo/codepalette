#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    // 
    int a = 10;
    while (a < 20) {
        printf("a : %d\n", a);
        a++;
    }

    // for (선언, 조건, 증감식) {실행}
    int i;
    for (i = 0; i < 10; i++) {
        printf("i: %d\n", i);
    }

    // do while- 조건식이 거짓이라도 한번은 실행함.
    a = 10;
    do {
        printf("a : %d\n", a);
        a++;
    } while (a < 1);

    return 0;
}