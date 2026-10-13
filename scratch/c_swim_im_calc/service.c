#include "data.h"
#include "core.h"
#include <stdio.h>



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
    else printf("[ERR] 계산되지 않음\n");

}