#include <stdio.h>
#include <stdlib.h>

int main(void) {

    // 메모리 할당.
    int *pi = malloc(sizeof(int)*5);
    if (pi == NULL) {
        printf("메모리할당 실패 ");
        return -1;
    }

    // 입력 섹션
    int i;
    for (i = 0; i < 5; i++) {
        *(pi + i) = (i + 1) * 100;
    }

    // 출력 섹션
    for (i = 0; i < 5; i++) {
        printf("i : %d \n", *(pi + i));
    }

    //메모리 반환
    free(pi);

    return 0;
}