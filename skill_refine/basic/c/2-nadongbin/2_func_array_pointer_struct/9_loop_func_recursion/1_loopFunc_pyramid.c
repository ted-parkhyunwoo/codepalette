#include <stdio.h>

// 반복함수로 숫자 피라미드 
// 반복함수는 오직 for/while 문 구성.

void pyramid(int a){
    int i, j;
    for (i = 0; i < a; i++){
        for (j = 1; j <= i + 1; j++){
            printf("%d", j);
        }
        printf("\n");
    }
}

int main(void){

    printf("숫자를 몇 층 쌓음? :");
    int num;
    scanf("%d", &num);
    pyramid(num);



    return 0;
}