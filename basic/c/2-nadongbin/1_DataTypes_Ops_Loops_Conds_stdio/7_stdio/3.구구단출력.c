#include <stdio.h>

int main(void){

    int x, i;
    printf("안녕하세요");
    printf("구구단의 단수(int)입력 : ");
    scanf("%d", &x);
    for (i = 1; i <= 9; i++){
        printf("%d x %d = %d\n", x, i, x*i);
    }
    return 0;
}
