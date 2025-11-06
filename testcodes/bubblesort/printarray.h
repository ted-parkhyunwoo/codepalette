#pragma once
#include <stdio.h>

void printDoubleArray(double* arr, unsigned sz) {
    printf("[");
    if (sz <= 0) {
        printf("]\n");
        return;
    }
    printf("%lf", arr[0]);
    for (unsigned i = 1; i < sz; ++i) {
        printf(", %lf", arr[i]);
    }
    printf("]\n");
}