#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char str[] = "ABC";
    str[0]='a';
    char str2[] = "abc";
    strcpy(str, str2);
    printf("%s\n", str);
    char* test = malloc(sizeof(char) * 10);

    strcpy(test, str);
    printf("%s\n", test);

    int maximum = 60;
    test = realloc(test, sizeof(char) * (maximum + 1));
    for (int i = 0; i < maximum; ++i) {
        test[i] = 'A' + i;
    }
    test[maximum] = '\0';
    printf("%s\n", test);
    free(test);



    return 0;
}