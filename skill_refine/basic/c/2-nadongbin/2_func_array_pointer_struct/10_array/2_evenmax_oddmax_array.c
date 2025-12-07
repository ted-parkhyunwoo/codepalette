#include <stdio.h>
#define NUMBER 5

int main(void){

    int array[NUMBER];
    int i, evemMax, oddMax;
    oddMax = 0;
    evemMax = 0;

    for (i = 0; i < NUMBER; i++){
        scanf("%d", &array[i]);
        if (array[i] % 2 == 0){
            if (array[i] > evemMax){
                evemMax = array[i];
            }
        } else {
            if (array[i] > oddMax){
                oddMax = array[i];
            }
        }
    }
    
    printf("Even Max : %d   Odd Max : %d \n", evemMax, oddMax);
    return 0;
}