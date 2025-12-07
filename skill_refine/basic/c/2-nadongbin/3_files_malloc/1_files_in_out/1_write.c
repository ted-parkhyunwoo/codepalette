#include <stdio.h>

int main(void){

    FILE *fp = NULL;
    fp = fopen("output.txt", "w");
    //쓰기모드. r-읽기.
    if (fp == NULL) {
        printf("Fail to file open.\n");
    } else {
        printf("Success.");
    }

    
    // File PUT Character.
    fputc('H', fp);
    fputc('E', fp);
    fputc('L', fp);
    fputc('L', fp);
    fputc('O', fp);
    fclose(fp);
    return 0;
}