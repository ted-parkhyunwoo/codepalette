#include <stdio.h>
#include <limits.h>

int main(void)
{
    int x = INT_MAX;         //INT_MAX는 C언어에 내장된 int가 가질 수 있는 가장 큰 수(limits.h)
    printf("%d\n", x);       // 2147483647
    printf("%d\n", x+1);    // 메모리를 넘어가서 음수가 되어버림.

    return 0;
}
