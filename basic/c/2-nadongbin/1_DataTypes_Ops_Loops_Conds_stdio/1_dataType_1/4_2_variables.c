#include <stdio.h>
#include <limits.h>

int main(void)
{
    int x = 10;
    int y = 20;
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("x + y = %d\n", x + y);
    printf("x - y = %d\n", x - y);
    printf("x * y = %d\n", x * y);
    printf("x / y = %d\n", x / y);      //int형이라 0으로 나옴.
    return 0;
}
