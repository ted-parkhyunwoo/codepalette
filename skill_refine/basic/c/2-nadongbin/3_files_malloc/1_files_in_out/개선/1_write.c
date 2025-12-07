#include <stdio.h>

int main(void) {
    FILE *fp = fopen("output.txt", "w");
    if (fp == NULL) {
        printf("파일 열기 실패.\n");
        return 1; // 실패 시 1 반환
    }

    // 파일에 문자 쓰기
    const char* text = "HELLO";
    for (int i = 0; text[i] != '\0'; i++) {
        fputc(text[i], fp);
    }

    fclose(fp); // 파일 닫기
    return 0;
}
