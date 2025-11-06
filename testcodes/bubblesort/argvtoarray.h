#pragma once
#include <stdlib.h>
#include <string.h>


double pow(const long x, long head) {
    double res = 1;
    const double dx = (double)x;
    const int isNegativeHead = head < 0;
    if (isNegativeHead) head *= -1;
    for (unsigned i = 0; i < head; ++i) {
        if (!isNegativeHead)
            res *= dx;
        else
            res /= dx;
    }
    return res;
}

double toDouble(const char* strNum) {
    return strtod(strNum, NULL);
}

double* argvToDoubleArray(int argc, char* argv[]) {
    if (argc <= 1) return NULL;
    double* res = malloc(argc * sizeof(double));
    for (unsigned i = 1; i < argc; ++i) {
        char* token = argv[i];
        res[i - 1] = toDouble(token);
    }
    return res;
}
