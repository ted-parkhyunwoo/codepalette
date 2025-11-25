#ifndef HELPER_H
#define HELPER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct intArr{
    int* array;
    unsigned sz;
} int_arr;

static void printArr(int* begin, int* end) {
    printf("{ ");
    if (end > begin) printf("%d", *begin);
    for (int* p = begin + 1; p < end; ++p)
        printf(", %d", *p);
    printf(" }\n");
}

void init_int_arr(int_arr* iArr, const unsigned sz, const unsigned max_int) {
    clock_t start = clock();
    iArr->sz = sz;
    iArr->array = (int*)malloc(sz * sizeof(int));
    int* p = iArr->array;
    for (unsigned i = 0; i < sz; ++i)
        *(p + i) = rand() % max_int + 1;
    printf("complete init sample: (%.6f seconds)\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}

void delete_int_arr(int_arr* iArr) {
    free(iArr->array);
}

void sort_int_arr(int_arr* iArr, void (*sortFunc)(int*, int*)) {
    int* begin = iArr->array;
    int* end = iArr->array + iArr->sz;
    sortFunc(begin, end);
}

static int compare_for_qsort(const void* a, const void*b) {
    return *(const int*)a - *(const int*)b;
}

static void is_sort_work_correctly(void (*sortFunc)(int*, int*)) {
    const unsigned size = 1000;
    int* sample = (int*)malloc(sizeof(int) * size);
    int* sorted = (int*)malloc(sizeof(int) * size);
    for (unsigned i = 0; i < size; ++i) {
        sample[i] = rand() % 10000 + 1;
        sorted[i] = sample[i];
    }

    sortFunc(sample, sample + size);
    qsort(sorted, size, sizeof(int), compare_for_qsort);

    int res = 1;
    for (unsigned i = 0; i < size; ++i)
        if (sample[i] != sorted[i]) {
            res = 0;
            break;
        };

    free(sample);
    free(sorted);
    printf("%s\n", res ? "validate sort: ok": "sort: fail");
}

void bench_sort_int_arr(int_arr iArr, void (*sortFunc)(int*, int*), const int directSort) {
    int* cp;
    if (!directSort) {
        cp = (int*)malloc(iArr.sz * sizeof(int));
        memcpy(cp, iArr.array, iArr.sz * sizeof(int));
    } else cp = iArr.array;

    const clock_t start = clock();
    sortFunc(cp, cp + iArr.sz);
    printf("result time: %.6f s (size: %d)\n", (double)(clock() - start) / CLOCKS_PER_SEC, iArr.sz);
    if (!directSort)
        free(cp);
}

void print_int_arr(const int_arr iArr) {
    const int* p = iArr.array;
    const unsigned sz = iArr.sz;
    printf("{ ");
    if (sz >= 1)    printf("%d", *p);
    for (unsigned i = 1; i < sz; ++i)
        printf(", %d", *(p + i));
    printf(" }\n");
}

#endif
