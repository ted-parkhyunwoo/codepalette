#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

bool isEven(size_t num) {
    return !(num % 2);
}

bool isPrime(size_t num) {
    bool res = true;
    if (num <= 1) return false;
    if (num == 2) return true;
    if (isEven(num)) return false;
    for (unsigned long long i = 3; i * i <= num ; i += 2) {
        if (num % i == 0) {
            res = false;
            break;
        }
    }
    return res;
}

void prime(size_t end, bool justCount) {
    size_t sz = 0;
    size_t* arr = (size_t*)calloc(0, sizeof(size_t));
    if (arr == NULL) {
        perror("[FATAL ERROR] Memory allocate error.\n");
        return;
    }
    
    for (size_t i = 0; i <= end; ++i) {
        if (isPrime(i)) {
            sz++;
            arr = (size_t*)realloc(arr, sz * sizeof(size_t));
            if (arr == NULL) {
                perror("[FATAL ERROR] Memory reallocate error.\n");
                free(arr);
                return;
            }
            arr[sz - 1] = i;
        }
    }

    // print
    if (!justCount) {
        for (size_t i = 0; i < sz; ++i) {
            printf("%zu ", arr[i]);
        }
        printf("\n");
    }
    printf("%zu 개\n", sz);

    free(arr);
}

void prime_che(size_t end, bool justCount)  {
    // 작성중.
    // 3부터 모든 수 나열
    // 짝수제거
    // 남은 수중 가장 작은수의 배수들을 작은수를 제외하고 제거
    // 위를 반복(배수가 없는 구간"end / 2"까지)
}


int main() {
    prime(100000000, true);
    return 0;
}