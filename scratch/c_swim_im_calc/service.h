// core.h 를 service에서 사용자단 래핑.
// 현재 goal 은 main.c 에서 받고있으며 기본값은 90으로 설정됨.
//      -> 직접입력된 매개변수가 있다면 마지막 매개변수가 목표치로 수정가능.

/* 
int argc, char* argv[] 기반으로 받으므로 
    cmd: './파일명 각 기록' 
    e.g:    ./a.out 17.3 21.6 26.3 18.5
방식으로 연달아 입력하면 wrapper에서 계산해줌

만약! 파일명으로만 실행된 경우 ->
    사용자의 입력을 직접 요구받게 됨.
*/


#ifndef SERVICE_H
#define SERVICE_H

#include "data.h"

// [Printer]    imResult 구조체를 읽기 쉽게 출력함
void printResultString(imResult* imres);

// [Wrapper]    최종 사용자단 래퍼함수. core.c의 calc 함수와 Printer를 결합함
void wrapper(int argc, char* argv[], double goal);

// [Wrapper]    파일실행 매개변수 입력이 없는 경우 사용자에게 기록을 직접입력을 받아 wrapper 호출
void userInsertMode(int goal);


#endif