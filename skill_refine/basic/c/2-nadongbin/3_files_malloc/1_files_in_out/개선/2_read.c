#include <stdio.h>

int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("파일 열기 실패.\n");
        return 1; // 실패 시 1 반환
    }

    int c;
    // 파일 끝에 도달할 때까지 문자 읽기
    while ((c = fgetc(fp)) != EOF) {
        putchar(c); // 화면에 문자 출력
    }

    fclose(fp); // 파일 닫기
    return 0;
}
