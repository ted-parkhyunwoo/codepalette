#include <stdio.h>

// 기존 강의 내용과 좀 다르게 최적화 수정함.
int main(void){

    int i, j;
    int guguArray[8][9];
    for (i = 2; i <= 9; i++){
        printf("\n[%d 단]\n", i);
        for (j = 1; j <= 9; j++){
            guguArray[i-2][j-1] = i * j;
            printf("%d x %d = %d\n", i, j, guguArray[i-2][j-1]);
        }
    }
    return 0;
}