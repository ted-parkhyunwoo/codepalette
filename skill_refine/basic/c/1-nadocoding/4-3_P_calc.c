#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// 문이 5개 있고, 각 문마다 어려운 수식퀴즈 출제 (랜덤)
// 맞히면 통과, 틀리면 실패

int getRandomNumber(int level);
void showQuestion(int level, int num1, int num2);

int main(void)

{
    srand(time(NULL));
    int count = 0;
    for (int i = 1; i <= 5; i++)
    {
        // x * y = ?
        int num1 = getRandomNumber(i);
        int num2 = getRandomNumber(i);
        //i를 이용해 어려운 숫자 출제
        
        //printf(문제)
        showQuestion(i, num1, num2);

        int answer;

        scanf("%d", &answer);
        if (answer == num1 * num2)
        { 
            printf("정답입니다. \n");
            count++;
        }
        else
        {
            printf("오답입니다. \n");
            
        }

        if (i ==5)
            {
                printf("5 문제중 %d문제를 맞혔습니다. \n", count);
            }

    }

    return 0;

}

int getRandomNumber(int level)
{
    return rand() % (level * 7) + 1;
}

void showQuestion(int level, int num1, int num2)
{
    printf("%d번 문제.  %d * %d = ? \n", level, num1, num2);
}
