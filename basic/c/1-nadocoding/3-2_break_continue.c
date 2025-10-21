#include <stdio.h>

int main(void)
{
    //1번 문제. 100까지 반복중, 10에 도달하면 종료.
    for (int i = 1; i < 100; i += 1)
    {
        printf("%d \n", i);

        if (i == 10)
        {
            break;
        }
    }
    //2번 문제. 20까지 반복출력하되, 3의 배수는 표시하지 않음.
    for (int j = 1; j <= 20; j++)
    {

        if (j % 3 == 0)
        {
            continue;
        }

        printf("%d \n", j);
    }
    // 3번 문제. 정수 입력 받아 합 계산. -1을 입력시 합계 출력후 종료
    
    int result = 0;
    int input_add;

    while (1)
    {
        printf("입력: ");
        scanf("%d", &input_add);

        //-1입력은 합산에 포함하지 않음. 종료명령.
        if (input_add == -1)
        {
            printf("결과 : %d \n", result);
            break;

        }
        printf("이전:%d, + %d = %d \n", result, input_add, result + input_add);  
        result += input_add;
    }

    // 4번 문제. 홀수, 짝수 입력을 연속적으로 받아, 홀수입력시 종료.
    
    
    printf("짝수 입력 검사기 입니다. \n");
    do
    {
        int user_input;
        printf("입력 : ");
        scanf("%d", &user_input);
        if (user_input % 2 == 0)
        {
            printf("%d 는 짝수 입력 입니다. 통과. \n", user_input);
            continue;
        }
        else
        {
            printf("%d 는 홀수 입니다. 프로그램을 종료합니다.", user_input);
            break;
        }
    }
    while (1);
    

    return 0;

}
