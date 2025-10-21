#include <stdio.h>
int main(void)
{
    // 참고 : ascii 코드 = ANSI (미국표준협회) 에서 제시한 표준 코드 체계.
    // 7bit, 총 128개 코드 (0~127)
    // a : 97
    // A : 65
    // 0 : 48
    // \0 : 0
    // \n : 10

    for (int i = 0; i < 128; i++)
    {
        printf("%d : %c\n", i, i);
    }

    // 입력한 문자열의 아스키보기. 각 영어와 한글.
    char str_eng[] = "abcdefg";
    for (int i = 0; i < sizeof(str_eng); i++)
        printf("%d\n", str_eng[i]);

    char str_kor[] = "가나다";
    for (int i = 0; i < sizeof(str_kor); i++)
        printf("%d\n", str_kor[i] );
    
    return 0;
}
