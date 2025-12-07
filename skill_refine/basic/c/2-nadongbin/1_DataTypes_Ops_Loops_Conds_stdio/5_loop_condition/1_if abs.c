#include <stdio.h>

int main(void)

{
    int x = -150;
    if (x < 0)
    {
        x *= -1;
    }
    printf("x의 절대값은 %d \n", x);
    return 0;
}
