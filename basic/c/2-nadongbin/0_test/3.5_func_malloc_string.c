#include <stdio.h>
#include <stdlib.h>

void inputStrings(char **strings, int count) {
    for (int i = 0; i < count; i++) {
        printf("Enter string %d: ", i + 1);
        scanf("%s", *(strings + i)); // 포인터를 사용하여 문자열 입력
    }
}

void printStrings(char **strings, int count) {
    for (int i = 0; i < count; i++) {
        printf("String %d: %s\n", i + 1, *(strings + i)); // 포인터를 사용하여 문자열 출력
    }
}

int main() {
    int count;
    char **strings;

    printf("Enter the number of strings: ");
    scanf("%d", &count);
    getchar(); // scanf 후 입력 버퍼에 남아있는 개행 문자 제거

    // 동적 메모리 할당으로 문자열 포인터 배열 생성
    strings = (char **)malloc(count * sizeof(char *));
    for (int i = 0; i < count; i++) {
        *(strings + i) = (char *)malloc(101 * sizeof(char)); // 각 문자열에 대한 메모리 할당
    }

    inputStrings(strings, count);
    printStrings(strings, count);

    // 할당된 메모리 해제
    for (int i = 0; i < count; i++) {
        free(*(strings + i));
    }
    free(strings);

    return 0;
}
