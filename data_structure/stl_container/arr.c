#include <stdio.h>
#include <stdlib.h>

int main() {
    int sz = 0;
    printf("Array Size: ");
    scanf("%d", &sz);
    puts("");
    // 동적할당 배열
    int *array = (int*)malloc(sizeof(int) * (sz + 1));
    // 자동할당 배열
    int array2[] = {1,2,3};

    for (int i = 0; i < sz; i++) {
        printf("index %d: ", i);
        scanf("%d", &array[i]);
    }

    puts("[RESULT]:");
    for (int i = 0; i < sz; i++) {
        printf("index %d: %d\n", i, array[i]);
    }    

    free(array);
    return 0;
}