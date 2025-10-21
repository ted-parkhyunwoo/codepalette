#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int level;
int arrayFish[6];
void initData();

int * cursor;
void printfFish();
void decreaserWater(long elapsedTime); 
int checkFishAlive();

int main(void)
{
    long startTime = 0; // 게임 시작 시간
    long totalElapsedTime = 0; // 총 경과 시간 
    long prevElapsedTime = 0; // 직전 경과 시간 (최근에 물 준 시간 간격)

    int num; // 몇번 어항에 물을 줄 것인지, 사용자 입력
    initData();

    cursor = arrayFish; // cursor[0], cursor[1] 처럼 사용할 것.

    startTime = clock(); // 현재 시간을 miliseconds (1000분의 1초) 단위로 반환

    while (1)
    {
        printfFish();
        // getchar(); // 임시로 입력 대기. 
        printf("\n 몇 번 어항에 물을 주시겠어요? ");
        scanf("%d", &num);

        // 입력값 체크
        if (num < 1 || num > 6)
        {
            printf("\n입력값이 잘못되었습니다.\n");
            continue;
        }

        //총 경과 시간
        totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;
        printf("총 경과 시간 : %ld 초 \n", totalElapsedTime);

        // 직전 물 준 시간 (마지막으로 준 시간) 이후로 흐른 시간
        prevElapsedTime = totalElapsedTime - prevElapsedTime;
        printf("최근 경과 시간 : %ld 초 \n", prevElapsedTime);

        // 어항의 물을 감소 (증발)
        decreaserWater(prevElapsedTime);

        // 사용자가 입력한 어항에 물을 준다.
        // 1. 어항의 물이 0이면? 물을 주지 않는다. (이미 고기가 죽음)
        //
        if (cursor[num - 1] <= 0)
        {
            printf("%d 번 물고기는 이미 죽었습니다. 물을 주지 않습니다\n", num);
        }
        // 2. 어항의 물이 0이 아닌경우 = 물을 준다. 100을 넘지 않는지 체크
        else if (cursor[num -1] + 1 <= 100)
        {
            //물을 준다
            printf("%d 번 어항에 물을 줍니다. \n\n", num);
            cursor[num-1] += 1;
        }

        // 레벨업을 할 건지 확인 (레벨업은 20초마다 한번씩 수행)
        if (totalElapsedTime / 20 > level - 1)      // 이 시간체크 로직 좀 어렵지만 중요. (1일때,2일때 등 고려)
        {
            //레벨업
            level++;
            printf(" 레벨업! 기존 %d에서 %d로 레벨업 \n\n", level-1, level);

            // 최종레벨 : 5
            if (level ==5)
            {
                printf("축하합니다. 최고레벨을 달성하였습니다. 게임을 종료합니다 \n");
                exit(0);
            }
        }

        // 모든 물고기가 죽었는지 확인
        if (checkFishAlive() == 0)
        {
            // 모두 죽음
            printf("모든 물고기가 죽었습니다. \n");
            exit(0);
        }
        else
        {
            //최소 1마리는 살아있음
            printf("물고기가 아직 살아있어요!\n");
        }

        prevElapsedTime = totalElapsedTime;
        // 최초 물준 시간 10초 -> 15 초때 물준다면 (5초 : prevElapsedTime -> 15초로 바꿈.) -> 25초 (10초로 되게)

    }

    return 0;
}

void initData()
{
    level = 1; // 게임 레벨 1~5)
    for (int i = 0; i < 6; i++)
    {
        arrayFish[i] = 100; // 어항의 물 높이 (0~100)
    }
}

void printfFish()
{
    printf(" %3d번  %3d번  %3d번  %3d번  %3d번 \n" , 1, 2, 3, 4, 5);
    for(int i = 0; i < 5; i++)
    {
        printf(" %5d ", arrayFish[i]);
    }
}

void decreaserWater(long elapsedTime)
{
    for (int i = 0; i < 6; i++)
    {
        arrayFish[i] -= (level * 3 * (int)elapsedTime); // 3은 난이도 조절을 위한 값. 
        if (arrayFish[i] < 0)
        {
            arrayFish[i] = 0;
        }
    }
}

int checkFishAlive()
{
    for (int i = 0; i < 6; i++)
    {
        if (arrayFish[i] > 0)
            return 1;
    }
    return 0;
}
