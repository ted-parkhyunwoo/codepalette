#include <stdio.h>
#include <string.h>

int main(void) {
    char fname[256];
    printf("파일 이름을 입력하세요: ");
    scanf("%s", fname);

    FILE *fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("파일 '%s' 열기 실패.\n", fname);
        return 1; // 실패 시 1 반환
    }

    char word[256];
    printf("검색할 단어를 입력하세요: ");
    scanf("%s", word);

    char buffer[256];
    int line = 0;
    // 파일 끝에 도달할 때까지 라인 읽기
    while (fgets(buffer, sizeof(buffer), fp)) {
        line++;
        if (strstr(buffer, word)) { // 단어가 라인에 포함되어 있는지 확인
            printf("라인 %d: %s", line, buffer);
        }
    }

    fclose(fp); // 파일 닫기
    return 0;
}
