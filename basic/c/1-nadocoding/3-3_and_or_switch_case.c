#include <stdio.h>
#include <time.h>       // time 사용 위해
#include <stdlib.h>     //rand, srand 사용 위해

int main(void)
{
    // && = and,  || = or.

    int a = 10;
    int b = 10;
    int c = 12;
    int d = 13;
    if (a == b || c == d)
    {
        printf("a와b 혹은 c와d 의 값이 같습니다. \n");
    }

 
    /* 
    //기존의 랜덤 가위바위보.
    //가위0 바위1 보2
    //무작위 수 뽑을때 srand, rand를 쓰려면  time.h를 로드 해야함. stdlib.h도 필요할 수 있음.
    //rand를 그냥 쓰면 rand결과가 계속 똑같이 출력된다.
    srand(time(NULL));  // !!!난수 초기화. 난수를 쓸땐 꼭 해야함!!!
    int i = rand() % 3; // 0 -2 반환. rand로 뽑을땐 꼭! srand로 난수초기화를 한다.

    if (i == 0)
    {
        printf("가위\n");
    }
    else if(i == 1)
    {
        printf("바위\n");
    }
    else if(i == 2)
    {
        printf("보\n");
    }
    else
    {
        printf("잘못된 출력\n");
    }

*/

    // switch case를 이용한 가위바위보
    // 위와 같은 상황을 만드려면 switch는 break;를 꼭 넣어야 함
    // break; 를 안넣으면 그 아래로 다 실행함.
    srand(time(NULL));
    int j = rand() % 3; // 0 -2 반환. 공부해야 하는 부분
    switch (j)
    {
        case 0:printf("가위\n"); break;
        case 1:printf("바위\n"); break;
        case 2:printf("보\n"); break;
        default:printf("잘못된 출력\n"); break;
    }
        



    return 0;

}
