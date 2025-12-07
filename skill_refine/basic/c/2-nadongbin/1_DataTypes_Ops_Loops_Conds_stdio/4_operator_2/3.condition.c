#include <stdio.h>


int main(void)
{
    int x = 50, y = 30;
    int absoluteX = (x > 0) ? x : -x;   //절대값으로 이렇게 자주 만듬. 참이면 좌, 거짓이면 우. 조건연산자.

    int max = (x > y) ? x : y;
    int min = (x < y) ? x : y;
    printf("x의 절대값 = %d\n", absoluteX);
    printf("x와 y중 최대값 = %d\n", max);
    printf("x와 y중 최소값 = %d\n", min);

    return 0;
}
