#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *pptr = malloc(sizeof(char)*5);
    if (pptr == NULL) {
        printf("Fail");
        return -1;
    }

    int i;

    for (i = 0; i < 5; i++) {
        *(pptr + i) = 'a' + i;
    }

    for (i = 0; i < 5; i++) {
        printf("%c ", *(pptr + i));
    }

    free(pptr);

    return 0;
}