#include <stdio.h>
#include <string.h>

int main(void) {

    char inputOne[5] = "A";
    char inputTow[5] = "B";
    printf("Difference : %d\n", strcmp(inputOne, inputTow));

    // 문자열 비교. 같으면 0, 틀리면 사전순 차이로 표기.
    // A 기준 B 라면 -1 (현재코드기준.)

    return 0;
}