#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//! 더 많은 c 문자열에 관한 내용은 이전에 작성해둔 메모를 참고.(./learning/c_string/) 

int main(int argc, char* argv[]) {

    // 문자의 배열(문자열) 은 항상 끝에 널문자:\0 이 와야 문장의 끝을 알림.
    char s1[6] = {'H', 'E', 'L', 'L', 'O', '\0'};
    printf("%s\n", s1); 

    char s2[] = "Hello";
    s2[0] = 'h';
    printf("%s\n", s2);

    char* s3 = "HeLlO";
    // s3[0] = 'h';     불가능. 문자열을 char *로 선언과 초기화시 읽기전용메모리로 작성되는것으로 알고있음.-> OK.
    printf("%s\n", s3);

    // 한글은 환경에 따라 2~3bytes 차지하므로 크게 설정
    // 5글자 *3 +널문자 1을 포함한 16도 잘못표현됨.
    char s4[17] = "알녕하세요";
    // s4[0] = '안';       // 공간문제에 따라서 부분변경 난해. 해야만 한다면 wchar_t 사용(유니코드 문자 타입).   
    // s4 = "안녕하세요";       // 불가. 문자열 변경 고려 안할시 차라리  char* 사용이 나음.
    printf("%s\n", s4);


    /* 문자열 함수들.
    strcpy(str1, str2) : str1에 str2를 복사
    strcat(str1, str2) : str1 뒤에 str2를 붙임.
    strlen(str) : 문자열의 바이트수를 구함 (영문이 아니라면 글자수를 구하는 방법은 없다고 보면 됨.(특문,영문,숫자는 1바이트. 한글은 2~3바이트 뒤죽박죽이므로.)) 주의:널문자 제외됨
    */

    char str1[15] = "Hello";
    char str2[15] = "World";
    char str3[15];
    int len;

    strcpy(str3, str1);
    printf("str3: %s\n", str3);
    printf("%d\n", strlen(str3));

    strcat(str3, str2);
    printf("str3: %s\n", str3);
    printf("%d\n", strlen(str3));

    printf("%d\n", strlen("안녕하세요 반갑습니다!"));

    return 0;
}