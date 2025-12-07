#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    FILE *fp;

    //! 파일쓰기.혹은 이어붙이기. 
    // r, w, a, r+, w+, a+ 등이 있음
    fp = fopen("test.txt", "w+");   // w+: 덮어씌움. a+ 이어붙임
    fprintf(fp, "%s", "abcd efgh\nijkl");
    fclose(fp);


    //! 읽어오기.
    fp = fopen("test.txt", "r");
    char a1[255];
    // fscanf(fp, "%s", a1);            // 문자만.
    // fscanf(fp, "%[^\n]", a1);        // 공백 포함

    fgets(a1, sizeof(a1), fp);          // 개행,공백 포함
    printf("%s", a1);
    // 한줄씩 진행되므로 다시입출력.
    fgets(a1, sizeof(a1), fp); 
    printf("%s\n", a1);

    // fgets의 사실상 올바른 사용법은 while문 사용.
    fp = fopen("test.txt", "r");
    while (fgets(a1, sizeof(a1), fp) != NULL) {
        printf("%s", a1); // 각 줄에 개행 포함
    }
    printf("\n");
    fclose(fp);
    return 0;
}