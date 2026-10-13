#include "imcalc.h"

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

