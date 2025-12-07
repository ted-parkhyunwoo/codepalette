#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int *pptr = malloc(sizeof(int)*5);
    if (pptr == NULL) {
        printf("Fail");
        return -1;
    }

    int i;
    for (i = 0; i < 5; i++) {
        *(pptr + i) = i + 1;
    }

    for (i = 0; i < 5; i++) {
        printf("%d ", *(pptr + i));

    }

    free(pptr);

    return 0;
}