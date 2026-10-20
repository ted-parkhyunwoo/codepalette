#include <stdio.h>
#include "data.h"
#include "core.h"
#include "service.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {

    // 목표치는 메인함수에서 다루는 중
    double GOAL = 90;

    // 매개변수가 총 5개일 경우 마지막 매개변수는 목표치로 설정하도록 함
    if (argc == 6 && isNumberStr(*(argv + 5)))
        GOAL = atof(argv[5]);

    // 매개변수가 과도하게 입력된 경우 계산하지 않고 바로 종료 (-1 리턴)
    if (argc > 6) {
        printf("매개변수 오류\n");
        return -1;
    }        
            
    if (argc > 1)       wrapper(argc, argv, GOAL);
    else                userInsertMode(GOAL);           // 매개변수가 입력되지 않은경우 이쪽으로 진입

    return 0;
}

