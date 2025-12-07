#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    
    FILE* fp;
    fp = fopen("./test.txt", "w+");
    printf("message: \n");
    while (1) {
        char bf[255];
        // scanf 로는 문제가 좀 있음.(개행 등.)
        fgets(bf, sizeof(bf), stdin);
        bf[strcspn(bf, "\n")] = 0;  // 개행문자 제거
        if (!strcmp(bf, "quit()") || !strcmp(bf, "exit()")) {
            break;
        }
        fprintf(fp, "%s\n", bf);
    }
    fclose(fp);

    return 0;
}