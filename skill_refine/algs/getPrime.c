#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef unsigned long long int ULL;
size_t* getPrime(const size_t end) {
    bool* isNotPrime = calloc(end + 1, sizeof(bool));
    isNotPrime[0] = isNotPrime[1] = true;

    // 주의: sqrt(end)를 사용하지 않고 i를 제곱하고 있음.
    for (ULL i = 2; i * i <= end; i++) { 
        if (!isNotPrime[i]) { for (size_t j = i * i; j <= end; j += i)  isNotPrime[j] = true; }
    }

    // make primes array: size추론하지 않음.(비용추가되므로)
    // 다음 limit는 gpt로 어림잡음. 리미트를 지정하지 않으면 메모리 할당 오류가능성(너무 큰 크기 할당)
    // 참고: 공학의 파이함수(숫자) 는 소수의 갯수를 말하는것이지, 원주율과 관련이 없음.
    size_t limit;
    if      (end < 10)              limit = 7;                      // 실제 π(10)=4, 넉넉하게 +3
    else if (end < 100)             limit = 30;                     // π(100)=25, 약간 여유
    else if (end < 1000)            limit = 180;                    // π(1000)=168
    else if (end < 10000)           limit = 1300;                   // π(10000)=1229
    else if (end < 100000)          limit = 9600;                   // π(100000)=9592
    else if (end < 1000000)         limit = 80000;                  // π(10^6)=78498
    else if (end < 10000000)        limit = 700000;                 // π(10^7)=664579
    else if (end < 100000000)       limit = 6000000;                // π(10^8)=5,761,455
    else if (end < 1000000000)      limit = 50000000;               // π(10^9)=50,847,534
    else if (end < 10000000000ULL)  limit = 460000000;              // π(10^10)=455,052,511
    else                            limit = end / 20 + 50000000;    // 매우 큰 수, 안전 여유

    size_t* primes = calloc(limit, sizeof(size_t));        
    size_t tmpIdx = 1;          // primes[0] 은 배열의 사이즈를 나타냄
    for (size_t i = 2; i <= end; ++i) { if (!isNotPrime[i])     primes[tmpIdx++] = i; }
    primes[0] = tmpIdx - 1;
    free(isNotPrime);

    return primes;
}

int main() {
    // 주의! 어림잡아 100억 까지만 계산됨. 이것 또한 64비트 기준. (체 방식의 문제점으로, 너무 큰 배열을 할당.)
    // 갯수만 세는 것과 다르게, 리턴배열을 또 할당하므로 100억 초과부터는 세그멘테이션 오류(메모리 할당오류)
    const size_t getPrimeTest = 10000000000;
    size_t* primes = getPrime(getPrimeTest);
    size_t size = 0;
    for (size_t i = 1; i <= primes[0]; ++i) { 
        // printf("%zu ", primes[i]); 
        size++; 
    }
    free(primes);

    printf("\nsize: %zu\n", size);

    return 0;
}
