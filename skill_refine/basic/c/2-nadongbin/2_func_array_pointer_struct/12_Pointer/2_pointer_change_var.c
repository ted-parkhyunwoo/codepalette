#include <stdio.h>

int main(void) {
    int x = 10;
    int *y = &x;
    printf("%d %d\n", x, *y);
    *y = 20;
    printf("%d %d\n", x, *y);
}