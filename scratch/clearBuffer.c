#include <stdio.h>


// 줄바꿈 제거
void clearWhiteSpaceInBuffer() {
    while (getchar() != '\n');
}


int main(int argc, char* argv[]) {

    int n;
    char str[50];
    char ch;

    printf("num: ");
    scanf("%d", &n);
    // 직접 제거 삽입
    while(getchar() != '\n');

    printf("string: ");
    scanf("%s", str);
    // 함수로 제거
    clearWhiteSpaceInBuffer();

    printf("char: ");
    scanf("%c", &ch);

    printf("\n\nresult\nnum: %d\nstring: %s\nchar: %c\n", n, str, ch);

    return 0;
}