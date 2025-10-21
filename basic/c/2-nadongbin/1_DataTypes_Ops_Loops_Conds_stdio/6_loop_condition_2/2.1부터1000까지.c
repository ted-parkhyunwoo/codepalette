#include <stdio.h>

int main(void)

{
    int i = 1, sum = 0;
    while (i <= 1000)
    {
        sum += i;
        i++;
    }

    printf("%d \n", sum);
    return 0;
}
