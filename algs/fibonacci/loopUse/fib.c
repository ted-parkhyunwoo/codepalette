#include <stdio.h>

typedef unsigned long long int ULL;
ULL getFib(int n) {
    if (n <= 1) return n;
    if (n > 92) {
        printf("Error: Index %d causes unsigned long long overflow.\n", n);
        return 0;
    }
    ULL f0 = 0;
    ULL f1 = 1;
    ULL tmp;
    for (int i = 1; i < n; ++i) {
        tmp = f0 + f1;
        f0 = f1;
        f1 = tmp;
    }
    return tmp;
}

