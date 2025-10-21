#include <stdio.h>

int main(void)

{
    int score = 85; //학생의 점수를 의미.
    if (score > 90)
    {
        printf("당신의 학점은 A 입니다. \n");
    }
    else if (score > 80)
    {
        printf("당신의 학점은 B 입니다. \n");
    }
    else if (score > 70)
    {
        printf("당신의 학점은 C 입니다. \n");
    }
    else
    {
        printf("당신은 F. 낙제입니다. \n");
    }

    return 0;
}
