#include <stdio.h>
#include <stdlib.h>

// 산술 관계 논리연산자

int main(int argc, char* argv[]) {
    
    // 1. 산술연산
    int a = 21;
    int b = 10;
    int c;

    c = a + b;
    printf("a + b = %d\n", c);
    c = a - b;
    printf("a - b = %d\n", c);
    c = a * b;
    printf("a * b = %d\n", c);
    c = a / b;
    printf("a / b = %d\n", c);
    c = a % b;
    // % 출력시 두개. \%가 아님.
    printf("a %% b = %d\n", c);

    int d = 10, e = 10, f = 10, g = 10;
    c = d;
    d = d + 1;
    printf("c, d : %d, %d\n", c, d);
    d = 10;

    // 대입후 증감
    c = d++;
    printf("c, d : %d, %d\n", c, d);
    // 증감후 대입
    c = ++e;
    printf("c, e : %d, %d\n", c, e);

    printf("\n");
    // 2. 관계연산
    a = 21;
    b = 10;
    c = '\0';

    c = a == b;
    printf("a == b: %d\n", c );
    c = a != b;
    printf("a != b: %d\n", c );
    c = a < b;
    printf("a < b: %d\n", c );
    c = a > b;
    printf("a > b: %d\n", c );
    c = a <= b;
    printf("a <= b: %d\n", c );
    c = a >= b;
    printf("a >= b: %d\n", c );

    printf("\n");
    // 3. 논리연산자
    a = 10 > 2;     // 1
    b = 10 > 20;    // 0
    c = 10 > 3;     // 1
    d = 10 > 30;    // 0

    e = a && b;
    printf("a && b : %d\n", e);
    e = a && c;
    printf("a && c : %d\n", e);

    e = b || c;
    printf("b || c = %d\n", e);
    e = b || d;
    printf("b || d = %d\n", e);
    e = !a;
    printf("!a : %d\n", e);
    e = !b;
    printf("!b : %d\n", e);
    // 응용
    f = 10;
    e = f >=5 && f <= 20;
    printf("e : %d\n", e);

    return 0;
}