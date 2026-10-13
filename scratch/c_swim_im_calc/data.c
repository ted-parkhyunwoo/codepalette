#include "data.h"
#include "imcalc.h"
#include <stdio.h>
#include <stdlib.h>

void clearImResult(imResult* res) {
    res->butterfly = 0;
    res->back = 0;
    res->back = 0;
    res->freestyle = 0;
    res->fix = 0;
}

imResult argsToImResult(int argc, char* argv[]) {
    imResult res;
    clearImResult(&res);
    int isValidArgs = 1;

    // 일단 매개변수가 4개를 넘어가면 조기 리턴 (0);
    if (argc > 5) {
        printf("[ERR]매개변수 %d로 4초과.\n", argc);
        return res; 
    }
    
    // [TODO]data import.
    for (int i = 1; i < argc; ++i) {
        char* bf = *(argv + i);
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
    char** bf = argv + 1;
    res.butterfly = atof(*bf++);
    res.back = atof(*bf++);
    res.breast = atof(*bf++);
    res.freestyle = atof(*bf);
    res.fix = 0;  

    return res;
}

