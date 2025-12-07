#include <stdio.h>

int main(void){

    int number, x, i, sum = 0;
    printf("입력할 정수의 갯수 : ");
    scanf("%d", &number);
    for (i = 0; i < number; i++){
        printf("정수 값 입력 : ");
        scanf("%d", &x);
        sum += x;
    }
    printf("전체 정수의 값은 %d 입니다. \n", sum);
    return 0;
}
