#include <stdio.h>

int main(void)
{
    //for (선언; 조건; 증감) {실행}
    for (int i = 2; i < 10; i++)
    {
        printf(" %d단\n", i);
        for (int j = 1; j < 10; j++)
            printf(" %d x %d = %d\n", i, j, i*j);

    }

    //while (조건) {실행}
    
    int a = 1;
    while (a < 6)
    {
        printf("%d\n", a++);
    }

    //do {동작} while (조건);
    int b = 1;

    do {
        printf ("%d\n", b);
        b += 1;
    } while (b < 6);

    //별 쌓기
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    //거꾸로별
    for (int i = 0; i < 5; i++)
    {
        for (int j = i; j < 4; j++)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("*");
        }
        printf("\n");
    }

    
    return 0;
}
