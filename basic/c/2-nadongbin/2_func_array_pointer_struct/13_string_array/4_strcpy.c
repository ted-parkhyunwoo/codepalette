#include <stdio.h>
#include <string.h>

int main(void) {
    char input[10] = "I Love You";
    char result[5] = "Love";

    //! 문자열 복사로, array크기가 달라도 포인터처럼 복사함.
    //! 심지어 공간이 작아도 복사.
    strcpy(result, input);
    printf("Result : %s \n", result);

    return 0;
}