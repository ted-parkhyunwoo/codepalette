#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    srand(time(NULL));
    printf("\n\n === 발모제 게임 시작 === \n\n");
    int answer; // 사용자 입력값
    int treatment = rand() % 4; // 발모제 선택 (0~3)

    int cntShowBottle = 0; // 이번 라운드에 보여줄 병의 개수
    int prevCntShowBottle = 0; // 전 라운드에 보여준 병의 개수
    // 전에 보여준 병의 개수를 기억하여 다음 라운드에는 다른 개수로 보여주기 위한 전략 (처음에 2개 -> 다음에는 3개 ..)

    // 3라운드의 게임 (3라운드의 발모제 공개)
    for (int i = 1; i <= 3; i++)
    {
        int bottle[4] = { 0, 0, 0, 0 }; // 4개의 병
        do {
            cntShowBottle = rand() % 2 + 2; // 보여줄 병의 개수 (0~1, +2 -> 2, 3)
        } while (cntShowBottle == prevCntShowBottle);
        prevCntShowBottle = cntShowBottle;

        int isIncluded = 0; // 보여줄 병 중에 발모제가 포함되었는지 여부 (1 : 포함)
        printf(" > %d 번째 라운드 : ", i);

        // 보여줄 병의 선택
        for (int j = 0; j < cntShowBottle; j++)
        {
            int randBottle = rand() % 4; // 0~3

            // 해당 병이 이미 선택되지 않았다면, 선택 처리
            if (bottle[randBottle] == 0)
            {
                bottle[randBottle] = 1;
                if (randBottle == treatment)
                {
                    isIncluded = 1;
                }
            }
            // 이미 선택된 병이라면, 중복이므로 다시 선택
            else
            {
                j--;
            }
        }

        // 사용자에게 정보 제공
        for (int k = 0; k < 4; k++)
        {
            if (bottle[k] == 1)
                printf("%d ", k + 1);
        }
        printf("번 병을 선택하였습니다\n\n");

        if (isIncluded == 1)
        {
            printf("  >> 축하 ! 머리가 났어요 !!\n");
        }
        else
        {
            printf("  >> 실패 ! 머리가 안났어요.. 다시 다시\n");
        }

        printf("\n ... 다음 라운드를 진행하려면 엔터를 누르세요 ...");
        getchar();
    }

    printf("\n\n발모제는 몇 번 병에 있었나요? ");
    scanf("%d", &answer);

    if (answer == treatment + 1)
    {
        printf("\n >> 정답입니다!\n");
    }
    else
    {
        printf("\n >> 아쉽! 답은, 발모제는 %d 번 병에 있었습니다\n", treatment + 1);
    }

    return 0;
}

