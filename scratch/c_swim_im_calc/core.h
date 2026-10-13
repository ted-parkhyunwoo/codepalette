#ifndef CORE_H
#define CORE_H

#include "data.h"

// string -> float 변환이 가능한지 boolean return.
int isNumberStr(const char* str); 

// imResult 구조체의 값을 0으로 초기화, 포인터로 사용하기 때문에 현재로썬 안쓰임.
void clearImResult(imResult* res);

// [Parser] string array (4개라고 가정함 주의) 를 기반으로 double로 전환하여 imResult 구조체로 변환
imResult strArrToImResult(char* strArr[]);

#endif