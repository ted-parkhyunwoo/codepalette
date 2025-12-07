#include <stdio.h>
#include "fib.h"

int main() {
    for (int i = 0; i < 100; ++i) {
        printf("%d: %llu\n", i, getFib(i));
    }
    return 0;
}
