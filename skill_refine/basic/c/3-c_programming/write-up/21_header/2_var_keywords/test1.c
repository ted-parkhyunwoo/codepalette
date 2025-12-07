#include <stdio.h>

int global_a = 100;
int global_b = 200;

void test1() {
    // printf("local_a1: %d\n", local_a1);
    // printf("local_a2: %d\n", local_a2);
}

void test2() {
    // static 선언시 함수내 변수가 다시 선언되더라도 값 유지.
    //! 정확히는 static이 전역화 하는건 맞지만, 새로 생성시에는 초기화 하고, 만약 재호출시 이미 생성한 전역화된 변수가 있다면 static int local_c = 100;식의 재선언은 무시됨.
    static int local_c = 100;
    local_c++;
    printf("local_c: %d\n", local_c);
}

void test3() {
    printf("global_a: %d\n", global_a);
    printf("global_b: %d\n", global_b);
}