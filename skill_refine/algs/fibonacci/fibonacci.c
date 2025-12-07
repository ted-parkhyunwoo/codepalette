#include <stdio.h>
#include <stdlib.h>
typedef unsigned long long int ULL;

//! 재귀식 타입.
ULL* memo = NULL;
void initMemo(int n) { 
    if (memo != NULL) free(memo);
    memo = (ULL*)calloc(n + 1, sizeof(ULL)); 

    if (memo == NULL) exit(EXIT_FAILURE);
    if (n >= 1)     memo[1] = 1;
}

ULL getFib(int n) {
    if (n < 0) exit(EXIT_FAILURE);
    if (n <= 1) return n;
    if (memo == NULL) exit(EXIT_FAILURE);

    if (n > 92) {
        printf("Error: Index %d causes unsigned long long overflow.\n", n);
        exit(EXIT_FAILURE);
    }

    if (memo[n] != 0) return memo[n];
    memo[n] = getFib(n - 1) + getFib(n - 2);

    return memo[n];
}

void freeMemo() { free(memo); }

