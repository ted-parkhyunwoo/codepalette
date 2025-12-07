#include <stdio.h>
#include "data.c"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {

    srand(time(NULL) * getpid());

    data test;
    data* ptr = &test;
    initData(ptr);

    for (long i = 0; i < 100000000; ++i) {
        int a = (rand() % 6) + 1;
        plusElement(ptr, a);
    }
    
    descData(ptr);

    return 0;
}