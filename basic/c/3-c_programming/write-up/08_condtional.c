#include <stdio.h>
#include <stdlib.h>

// 조건문, 분기문.

int main(int argc, char* argv[]) {
    int a = 10;
    int b = 20;

    // if
    if (a > b) {
        printf("a는 b 보다 큽니다\n");
    }
    if (a < b) {
        printf("a는 b보다 작습니다\n");
    }

    // if/else
    if (a > b) {
        printf("a는 b 보다 큽니다\n");
    } else {
        printf("a는 b보다 크지 않습니다.\n");
    }

    // if/else if/else
    if(a < 0) {
        printf("a는 0보다 작습니다\n");
    } else if(a < 5) {
        printf("a는 5보다 작습니다\n");
    } else if(a < 10) {
        printf("a는 10보다 작습니다\n");
    } else if(a < 20) {
        printf("a는 20보다 작습니다\n");
    } else {    
        printf("a는 20보다 작지 않습니다\n");
    }

    //switch
    switch(a) {
        case 0:
            printf("a = 0\n");
            break;
            //! break를 안걸면 다음조건이 안맞아도 연달아 실행됨.
        case 5:
            printf("a = 5\n");
            break;
        case 10:
            printf("a = 10\n");
            break;
        case 20:
            printf("a = 20\n");
            break;
        default:
            printf("어디에도 속하지않음.\n");
            //! 어디에도 없으면 실헹됨.
    }

    return 0;
}