#include "data.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printResultString(imResult* imres) {
    printf("[Result]\nButterfly: %.3f    Backstroke: %.3f    Breaststroke: %.3f    Freestyle: %.3f\nTotal: %.3f    Goal: %.3f    Result: %.3f\n",
        imres->butterfly, imres->back, imres->breast, imres->freestyle, imres->total, imres->goal, imres->result);
}

void wrapper(int argc, char* argv[], double goal) {
    imResult result = strArrToImResult(argv + 1);
    calc(&result, goal);

    if (result.isCalculated) {
        printResultString(&result);
    }
    else printf("[WRAPPER ERR] 계산되지 않음\n");

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
    for (int i = 0; i < 5; ++i)
        free(userRecord[i]);
    free(userRecord);
}