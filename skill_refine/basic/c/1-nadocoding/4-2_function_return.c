#include <stdio.h>

//함수 선언 
int calc(int total, int ate);

int main(void)
{
    // 함수 사용 
    printf("%d - %d = %d remain.\n", 5, 3, calc(5, 3));

    // 함수 사용의 응용.
    int input_total, input_ate;
    puts("total count :");
    scanf("%d", &input_total);
    puts("ate count :");
    scanf("%d", &input_ate);
    printf("%d remain.\n", calc(input_total, input_ate));

    return 0;
}

// 함수 정의 
int calc(int total, int ate)
{
    return total - ate;
}
