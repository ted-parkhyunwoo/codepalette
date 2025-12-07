#include <iostream>
#include "./lib/qsort.h"
#include <unistd.h>

int* getRandArr(int size, int max) {
    int* res = new int[size];
    for (int i = 0; i < size; ++i)
        res[i] = rand() % max + 1;
    return res;
}

int main() {
    srand(time(NULL) ^ getpid());
    int size = 100000000;
    int* sample = getRandArr(size, 10000);

    clock_t startTime = clock();
    quick(sample, sample + size);
    double timeRes = (double)(clock() - startTime) / CLOCKS_PER_SEC;

    printf("%.6f s\n", timeRes);

    delete[] sample;
    return 0;
}
