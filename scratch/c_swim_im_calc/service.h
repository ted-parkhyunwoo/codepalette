// core.h 를 service에서 사용자단 래핑.
// 현재 goal 은 main.c 에서 받고있으며 90으로 설정됨

/* 
int argc, char* argv[] 기반으로 받으므로 
    cmd: './파일명 각 기록' 
    e.g:    ./a.out 17.3 21.6 26.3 18.5
방식으로 연달아 입력하면 wrapper에서 계산해줌
*/


#ifndef SERVICE_H
#define SERVICE_H

#include "data.h"

// 출력함수
void printResultString(imResult* imres);
// 위 출력함수와 core.c를 결합한 최종 사용자단 래퍼함수(스택메모리 구조체 생성, 구조체 작성, 계산, 출력으로 이어짐)
void wrapper(int argc, char* argv[], double goal);


#endif