#include <stdio.h>
#include <stdlib.h>
#include "imcalc.h"
#include "data.h"

const double GOAL = 90;

int main(int argc, char* argv[]) {

    // isNumberStr function test
    /*
    char* arr[] = {"31", "42.1", ".13", "41.", "1.24", "-.", "-2", "-33.2", "-.24", "-231."};
    for (int i = 0; i < 10; ++i)
        printf("%s: %s\n", arr[i], isNumberStr(arr[i])? "ok" : "FALSE!!!");
    */

    int hasArgs = argc != 1? 1 : 0;

    if (hasArgs) {
        double res = 0;
        for (int i = 1; i < argc; ++i) {
            if (!isNumberStr(argv[i])) {
                printf("[ERR]%s is not number.\n", argv[i]);
                return -1;
            }
            res += atof(argv[i]);
        }
        printf("GOAL: %.2fs\nTOTAL : %.3fs (%+.2fs)\n", GOAL, res, res - GOAL);
    }


    imResult testRes = argsToImResult(argc, argv);

    printf("[test]: %f %f %f %f \n", testRes.butterfly, testRes.back, testRes.breast, testRes.freestyle);


    return 0;
}

