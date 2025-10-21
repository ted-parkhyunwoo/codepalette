#include <stdio.h>

int main(void)

{
    /*
        윤년 오차보정 과정. 
        4년마다 윤년. 100년단위는 해당안됨. 400년은 예외로 윤년
     */
    int year;
    puts("-1 to exit.");

    while (1)
    {
        printf("Year : ");
        scanf("%d", &year);
        if (year == -1)
        {
            break;
        }
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            printf("Leap Year. (%d) \n", year);
        }
        else
        {
            printf("Not Leap Year. (%d) \n", year);
        }
    }
    puts("exit");
    return 0;
}
