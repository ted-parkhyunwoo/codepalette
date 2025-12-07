#include <stdio.h>
#include <stdlib.h>

int func(int* p1, int* p2) {
    *p1 = 1;
    *p2 = 2;
    return 0;
}

void test(int a, int b) {
    printf("a: %d\n", a);
    printf("b: %d\n", b);
}


void add(int a, int b) { printf("add: %d\n", a + b); }
void sub(int a, int b) { printf("sub: %d\n", a - b); }
void process(void (*fn) (int, int), int a, int b) { fn(a, b); }


int main(int argc, char* argv[]) {
    
    int a1 = 100;   //기본자료형(일반)변수
    int *a2 = &a1;  //참조자료형(포인터)변수

    printf("a1 : %d\n", a1);
    printf("&a1: %p\n", &a1);
    printf("a2: %p\n", a2);
    printf("*a2: %d\n", *a2);

    *a2 = 200;
    printf("a1: %d\n", a1);

    //예상치 못한 버그발생을 피하기위해 널로 선언
    int* ptr = NULL;
    // printf("*ptr: %d\n", *ptr);  //주소값이 아니고 더미데이터라 오류출력됨.
    // int형으로 출력시에는 더미데이터 출력됨.

    if (ptr) {printf("주소설정됨\n");}
    else {printf("주소설정되지않음\n");}
    // NULL로 안하면 if문으로 진입되어버림.

    // pointer-pointer
    int b1 = 100;
    int* b2 = &b1;
    int** b3 = &b2;
    printf("%d\n", **b3);

    // pointer는 함수와 연동하여 사용하는 경우가 많음.
    int c1;
    int c2;
    func(&c1, &c2);
    printf("c1: %d, c2: %d\n", c1, c2);

    //! 함수포인터: 함수의 주소값을 포인터변수에 담아 함수호출
    void (*pt) (int, int);
    pt = test;
    pt(1, 2);
    void (*pt2) (int, int) = test;
    pt2(3, 4);

    // 좀더 복잡한 형태. (매개변수로 함수를 받고싶을 때)
    process(add, 100, 200);
    process(sub, 100, 50);

    return 0;
}