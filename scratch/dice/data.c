#include <stdio.h>
#define SIZE 6

typedef struct dataStruct {
    long count[SIZE];
} data;


void initData(data* d) {
    for (int i = 0; i < SIZE; ++i) {
        d->count[i] = 0;
    }
}

void descData(data* d) {
    for (int i = 0; i < SIZE; ++i) {
        printf("%d: %ld\n", i + 1, d->count[i]);
    }
}

void plusElement(data* d, unsigned num) {
    if (num > SIZE) return;
    d->count[num - 1]++;
}
