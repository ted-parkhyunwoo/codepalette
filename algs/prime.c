#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

bool isEven(size_t num) {
    return !(num % 2);
}

bool isPrime(const size_t num) {
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

void prime(const size_t end, const bool justCount) {
    size_t sz = 0;
    size_t* arr = (size_t*)calloc(0, sizeof(size_t));           // NULL과 같음
    if (arr == NULL) {
        perror("[FATAL ERROR] Memory allocate error.\n");
        return;
    }
    
    for (size_t i = 0; i <= end; ++i) {
        if (isPrime(i)) {
            sz++;
            size_t* tmp = (size_t*)realloc(arr, sz * sizeof(size_t));       // 재할당 실패중 누수를 막기위한 임시포인터
            if (tmp == NULL) {
                perror("[FATAL ERROR] Memory reallocate error.\n");
                free(arr);
                return;
            }
            arr = tmp;
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

void prime_che(const size_t end, const bool justCount) {
    bool* arr = (bool*)calloc(end + 1, sizeof(bool));
    // arr 는 prime인지를 보고 있지만, 만약 isNotPrime 으로 논리를 재정렬 하면 아래 초기화는 필요없을듯.
    for (size_t i = 2; i <= end; ++i) {
        arr[i] = true;
    }

    // sqrt(end) 최적화 적용안됨. end를 limit_i로 변경하고 아래 지침을 따라야함.
    // const size_t limit_i = (size_t)sqrt((double)end);          // math.h 추가하고, 컴파일시 -lm
    // for (size_t i = 2; i <= limit_i; ++i) {                     // end 와 limit_i 를 필요에 따라 수정할 것.
    for (unsigned long long i = 2; i * i <= end; i++) {     // 기존방식. i * i 에 오버플로우 위험

        if (arr[i]) {
            // i * 2가 맞지만, 이전 소수 제거 루프에서 이미 제거됐다고 함.
            for (size_t j = i * i; j <= end; j += i) {
                arr[j] = false;
            }
        }
    }

    // print
    size_t sz = 0;
    for (size_t i = 0; i <= end; ++i) {
        if (arr[i]) {
            sz++;
            if (!justCount)
                printf("%zu ", i);
        }
    }
    
    printf("\n%zu개\n", sz);
    free(arr);
}


int main() {
    const size_t test = 10000000000;
    // prime(test, true);               // 10억 초과시 굉장히 느림 주의.
    prime_che(test, true);           // 개선
    return 0;
}
