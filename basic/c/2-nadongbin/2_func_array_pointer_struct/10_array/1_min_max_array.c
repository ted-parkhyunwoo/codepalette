#include <stdio.h>
#include <limits.h>     // INT_MAX 를 쓰기위해
#define NUM 5

int main(void){
    int i, max, min, maxindex, minindex;
    max = 0;
    min = INT_MAX;      // 21474836417
    maxindex = 0;
    minindex = 0;

    int array[NUM];
    // array[0]~ array[4] 선언. 입력받음.
    for (i = 0; i < NUM; i++){
        scanf("%d", &array[i]);

        if(max < array[i]){
            max = array[i];
            maxindex = i;
        }

        if(array[i] < min){
            min = array[i];
            minindex = i;
        }
    }
    printf("최대값 : %d 인덱스 : %d \n", max, maxindex);
    printf("최소값 : %d 인덱스 : %d \n" , min, minindex);
    return 0;
}