#include "data.h"
#include <stdlib.h>
#include <stdio.h>

int isNumberStr(const char* str) {
    int dotIdx = -1;        // 앞으로 str내 . 의 인덱스가 없다면 -1로 취급됨
    const char* bf = str;
    if (*bf == '-') {
        bf++;
        if (*bf == '\0') return 0;    // "-" 형태의 문자열 0 리턴 
    }

    int i = 0;
    while (*bf != '\0') {
        if (*bf == '.') {
            if (dotIdx != -1) return 0;     // 점이 두개 출현시 0리턴
            if (i == 0) return 0;           // 첫문자가 .이면 0리턴
            dotIdx = i;
        } 
        else if (*bf < '0' || *bf > '9') return 0;  // else if문으로 . 외 문자 출현시 0리턴 
        bf++;
        i++;
    }
    
    if (*str == '-') dotIdx++;
    if (dotIdx != -1 && str[dotIdx] == '.' && str[dotIdx + 1] == '\0') return 0;    // 마지막문자가 .이면 0리턴
    
    // debug print.
    // printf("debug\t str: %s\t dotIdx: %d, i: %d\n", str, dotIdx, i);
    return 1;
}


void clearImResult(imResult* res) {
    res->butterfly = 0;
    res->back = 0;
    res->back = 0;
    res->freestyle = 0;
    res->isCalculated = 0;
    res->goal = 0;
    res->total = 0;
    res->result = 0;
}


imResult strArrToImResult(char* strArr[]) {
    imResult res;
    clearImResult(&res);

    // 입력검증(사용자의 문자열이 double 전환 가능한지) 실패시 convertError에 에러코드(1)가 삽입됨.
    for (int i = 0; i < 4; ++i) {
        char* bf = *(strArr + i);
        if (isNumberStr(bf)) 
            continue;
        
        clearImResult(&res);
        printf("[CORE STOP] '%s' is not a number. \n", *(strArr + i));
        res.convertError = 1;
        return res;
    }


    // argv 의 str 를 double로 변환후 imResult 구조체 res로 대입
    char** bf = strArr;
    res.butterfly = atof(*bf++);
    res.back = atof(*bf++);
    res.breast = atof(*bf++);
    res.freestyle = atof(*bf);
    res.total = res.butterfly + res.back + res.breast + res.freestyle;
    res.convertError = 0;

    return res;
}


void calc(imResult* imres, double goal) {
    if (imres->isCalculated) {
        printf("[CORE STOP] 이미 계산이 완료된 imResult 구조체\n");
        return;
    }

    if (imres->convertError) {
        printf("[CORE ERR] 문자열의 숫자전환 실패\n");
        return;
    }
 
    imres->goal = goal; // 굳이 1회성 출력에는 필요는 없으나 imResult 구조체에 일단 기록해둠 
    imres->result = imres->total - imres->goal; // 아래도 imres->goal 대신 goal 로 사용하면 1회성 사용 가능
    imres->isCalculated = 1;
}