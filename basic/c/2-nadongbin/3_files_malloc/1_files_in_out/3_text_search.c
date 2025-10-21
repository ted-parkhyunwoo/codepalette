#include <stdio.h>
#include <string.h>

int main(void) {

    FILE *fp;
    char fname[256];
    char buffer[256];
    char word[256];
    int line = 0;

    printf("File name : ");
    scanf("%s" , fname);

    printf("Searching words : ");
    scanf("%s", word);

    if ((fp = fopen(fname, "r")) == NULL){
        fprintf(stderr, "Can't not open file : %s\n", fname);
        return 0;
    }
    while (fgets(buffer, 256, fp)) {
        line++;
        if (strstr(buffer, word)) {
            printf("라인 %d : 단어 %s", line, word);
        }
    }

    return 0;
}