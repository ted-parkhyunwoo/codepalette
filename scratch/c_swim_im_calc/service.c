#include "data.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printResultString(imResult* imres) {
    printf("[Your Lap Record]\n\tButterfly: %.3f\n\tBackstroke: %.3f\n\tBreaststroke: %.3f\n\tFreestyle: %.3f\n[Result]\n\t%c%.3f (Total: %.3f    Goal: %.3f)\n",
        imres->butterfly, imres->back, imres->breast, imres->freestyle, imres->result>0?'+':'\0', imres->result, imres->total, imres->goal);
}

void wrapper(int argc, char* argv[], double goal) {
    imResult result = strArrToImResult(argv + 1);
    calc(&result, goal);

    if (result.isCalculated)        printResultString(&result);
    else                            printf("[WRAPPER ERR] 계산되지 않음\n");

}

void userInsertMode(int goal) {
    char* im[] = {"butterfly", "backstroke", "breaststroke", "freestyle"};

    // 메모리할당(사용자 입력 기록 string 저장)
    char** userRecord = malloc(sizeof(char*) * 5);
    for (int i = 0; i < 5; ++i)
        *(userRecord+i) = malloc(sizeof(char) * 20);

    // 사용자 입력
    for (int i = 0; i < 4; ++i) {
        printf("%s: ", *(im + i));
        scanf("%s", *(userRecord + i + 1));
    }

    // 계산
    wrapper(0, userRecord, goal);

    // 동적할당 해제
    for (int i = 0; i < 5; ++i)     free(userRecord[i]);
    free(userRecord);
}