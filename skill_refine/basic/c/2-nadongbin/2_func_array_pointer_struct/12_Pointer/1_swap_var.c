#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


int main(void) {
    int x, y;
    x = 1;
    y = 2;
    printf("%d, %d\n", x, y);
    swap(&x, &y);
    // 함수는 사용 후 초기화 되기 때문에, 포인터를 써야 값이 스왑됨.
    printf("%d, %d\n", x, y);

    
    return 0;
}