#include <stdio.h>
#include <stdlib.h>
#include "qsort.h"
#include <time.h>
#include <unistd.h>
int* getRandArr(int size, int max) {
    int* res = malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i) {
        res[i] = rand() % max + 1;
    }
    return res;
}

int isSorted(int* sorted, int* original, int size) {
    quick(original, original + size);
    for (int i = 0; i < size; ++i) {
        if (*(sorted + i) != *(original + i)) return 0;
    }
    return 1;
}


int main() {
    srand(time(NULL) ^ getpid());
    int size = 100000000;
    int* sample = getRandArr(size, 10000);
    clock_t startTime = clock();
    quick(sample, sample + size);
    double resTime = (double)(clock() - startTime) / CLOCKS_PER_SEC;

    printf("%.6f s\n", resTime);
    free(sample);
    return 0;
}
