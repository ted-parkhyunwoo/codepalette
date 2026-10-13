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
    res->fix = 0;
}

imResult strArrToImResult(char* strArr[]) {
    imResult res;
    clearImResult(&res);
    int isValidArgs = 1;

    
    // [TODO]data import.
    for (int i = 0; i < 4; ++i) {
        char* bf = *(strArr + i);
        if (isNumberStr(bf)) {
            continue;
        }
        isValidArgs = 0;
        break;
    }


    if (!isValidArgs) {
        clearImResult(&res);
        printf("Arguments ERR. exit\n");
        return res;
    }


    // 이래로는 argv 의 str 를 double로 변환후 res로 삽입
    char** bf = strArr;
    res.butterfly = atof(*bf++);
    res.back = atof(*bf++);
    res.breast = atof(*bf++);
    res.freestyle = atof(*bf);
    res.fix = 0;  

    return res;
}


