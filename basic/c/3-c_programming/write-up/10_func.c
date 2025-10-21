#include <stdio.h>
#include <stdlib.h>

// +@. 매크로. (함수처럼 보이지만 x 부위가 x++로 변경됨)
#define FUNC4(x) (x++)

// 함수형태 : 반환값 함수명 (매개변수타입 매개변수) {코드};

// 반환형이 없는함수 (+@ 로 포인터를 이용한 값 변경.)
void func(int* a) {
    (*a)++;
}

// 프로토타입, 메인함수 아래에서 함수선언
int func2();

// 여러 매개변수.
int func3(int a, int b) {
    return a + b;
}

int main(int argc, char* argv[]) {
    int a = 5;
    func(&a);
    printf("a: %d\n", a);
    
    int b = 'a';
    func(&b);
    printf("b: %c\n", b);

    int c = func2();
    printf("c: %d\n",c);

    int d = func3(a, c);
    printf("d: %d\n", d);

    int e = 3;
    FUNC4(e);
    printf("e: %d\n", e);

    return 0;
}

int func2() {
    return 100;
}