#include <stdio.h>
#include "fibonacci.h"

int main() {

    initMemo(100);

    for (int i = 0; i <= 100; ++i) {
        printf("%d: %llu\n", i, getFib(i));
    }

    freeMemo();

    return 0;
}