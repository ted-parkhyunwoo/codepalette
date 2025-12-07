#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)

{
    srand(time(NULL));
    int rand_num = rand() % 100 + 1; // 1~100
    int answer;
    int chance = 5;
    printf("UP & DOWN 게임을 시작합니다. \n");
    
    while (1)
    {
        printf("입력 : ");
        scanf("%d", &answer);

        if (answer == rand_num)
        {
            printf("축하합니다. 정답입니다. 게임을 종료합니다.\n");
            break;
        }

        else
        {   
            chance -= 1;
            if (chance == 0)
            {
                printf("남은 기회가 없습니다.\n정답은 %d 였습니다. 게임이 종료됩니다. \n", rand_num);
                break;
            }

            if (rand_num > answer)
            {
                printf("UP\n");
            }
            else
            {
                printf("Down\n");
            }
           
            printf("남은 기회 : %d\n", chance);
        }
    }
    return 0;
}
