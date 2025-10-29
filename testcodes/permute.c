#include <stddef.h>
#include <stdio.h>      //test

int factorial(int num) {
    int res = 1;
    for (int i = 1; i <= num; ++i) res *= i;
    return res;
}

// n 개중 r개 =  n! / (n - r)!
int oldPermute(int n, int r)  {
    if (n <= 0 || r <= 0) return -1;
    if (r > n) return 0;

    int left = factorial(n);
    int right = factorial(n - r);
    return left / right;
}

// 5P2라 칠때 5*4*3*2*1 / 3*2*1  = 5 * 4 로 줄여짐을 고려한 새로운 순열함수
//! 표준 자료형중에 제일 큰 정수형데이터. 20! 까지 연산가능 (2432902008176640000)
unsigned long long int permute(int n, int r) {
    unsigned long long int t = n - r;
    if (n <= 0 || n < r) return 0;
    if (t < 0) return -1;

    long res = 1;
    for (int i = n; i > t; i--) {
        res *= i;
    }
    return res;
}

//! 작성중
int* getPermuteArr(int* base, int baseSz, int select) {
    int tmp[permute(baseSz, select)];
    
}


int main() {
    int n = 20;
    int r = 20;

    printf("%ld\n", oldPermute(n, r));
    printf("%llu\n", permute(n, r));

    return 0;
}