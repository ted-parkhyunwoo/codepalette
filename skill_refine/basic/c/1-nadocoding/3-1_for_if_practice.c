#include <stdio.h>

int main(void)
{
    printf("구구단 프로그램 입니다.\n");
    printf("몇 단을 보시겠습니까? : ");
    
    //for 문 연습.
    int dan;
    scanf("%d", &dan);
    printf("%d 단 입니다.\n", dan);

    for (int k = 1; k <= 9; k++)
    {
        printf("%d x %d = %d\n", dan, k, dan * k);

    }
    
    printf("종료되었습니다. \n");


    //if 문 연습.
    printf("2~9 단도 보시겠습니까? (y or n) : ");

    char two_for_nine;
    scanf(" %c", &two_for_nine);

    if (two_for_nine == 'y')
    {
        for (int i = 2; i <= 9; i+= 1)
        {
            printf("%d 단\n", i);
            for (int j = 1; j <= 9; j++)
            {
                printf("%d x %d = %d\n", i, j, i*j);
            }
        }
    }
    else if (two_for_nine == 'n')

    {
    printf("보지 않습니다.\n");
    }

    else {
    printf("잘못된 입력입니다.\n");
    }



    return 0;
}


