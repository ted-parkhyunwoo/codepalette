#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "core.h"
#include "service.h"

const double GOAL = 90;

int main(int argc, char* argv[]) {

    // isNumberStr function test
    /*
    char* arr[] = {"31", "42.1", ".13", "41.", "1.24", "-.", "-2", "-33.2", "-.24", "-231."};
    for (int i = 0; i < 10; ++i)
        printf("%s: %s\n", arr[i], isNumberStr(arr[i])? "ok" : "FALSE!!!");
    */


    //! TEST1 : 프로토타입 코드 (매개변수를 직접 double 전환후 계산)
    // int hasArgs = argc != 1? 1 : 0;

    // if (hasArgs) {
    //     double res = 0;
    //     for (int i = 1; i < argc; ++i) {
    //         if (!isNumberStr(argv[i])) {
    //             printf("[ERR]%s is not number.\n", argv[i]);
    //             return -1;
    //         }
    //         res += atof(argv[i]);
    //     }
    //     printf("GOAL: %.2fs\nTOTAL : %.3fs (%+.2fs)\n", GOAL, res, res - GOAL);
    // }

    //! TEST2: core.c에 작성한 함수구현방식의 Test. (0번 매개변수는 파일명이므로 제외)
    // imResult testRes = strArrToImResult(argv + 1);
    // printf("[test]: %f %f %f %f \n", testRes.butterfly, testRes.back, testRes.breast, testRes.freestyle);
    // printf("[total test]:%.3f\n", testRes.total);
    // printf("%d %f\n", testRes.isCalculated, testRes.goal);


    //! TEST3: service 단의 최종 사용
    wrapper(argc, argv, 90);

    return 0;
}

