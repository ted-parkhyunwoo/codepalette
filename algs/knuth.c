#include <stdio.h>

// 점화식 h(new) = 3^h(old) + 1
int getKnuth(const int h) {
    int res = 0;
    for (int i = 0; i < h; ++i) {
        res = 3 * res + 1;
    }
    return res;
}

// 일반공식 = (3^k - 1) / 2
int getKnuth2(const int k) {
    int base = 1;
    for (int i = 0; i < k; ++i) {
        base *= 3;
    }
    return (base - 1) / 2;
}


int main() {
    for (int i = 1; i < 10; ++i) {
        printf("%d\n", getKnuth(i));
    }
    return 0;
}