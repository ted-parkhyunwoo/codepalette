#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//! 다시 작성해본 입력받은텍스트-> 파일저장. 윈도우즈, linux 정상 작동.
int main(int argc, char* argv[]) {
    
    FILE* fp;
    fp = fopen("text.tmp", "w+");

    printf("message: \n");
    char bf[255] = "";
    while (strcmp(bf, "quit()\n")) {
        fgets(bf, sizeof(bf), stdin);
        fputs(bf, fp);
    }

    fclose(fp);

    return 0;
}