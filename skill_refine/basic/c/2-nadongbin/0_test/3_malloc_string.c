#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    char* *pptr = malloc(sizeof(char*)*5);
    if (pptr == NULL) {
        printf("Fail");
        return -1;
    }

    int i;
    char* user_input;

    for (i = 0; i < 5; i++) {
        printf("Input : ");
        user_input = malloc(sizeof(char)*100);
        scanf("%s", user_input);
        *(pptr + i) = malloc(strlen(user_input) + 1);
        strcpy(*(pptr + i), user_input);
    }

    for (i = 0; i < 5; i++) {
        printf("%s ", *(pptr + i));
    }

    for (i = 0; i < 5; i++) {
        free(*(pptr + i));
    }

    free(pptr);

    return 0;
}