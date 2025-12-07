#include <stdio.h>
#include <stdlib.h>

// 키보드입출력

int main(int argc, char* argv[]) {


    // getchar와 putchar : 문자를 받거나 출력
    printf("문자입력: ");
    // char a = getchar();  // 기본사용법이나, 아래와같이 사용
    int a = getchar();  // EOF(-1) 구분을 위해 char 대신 int.
    if (a != EOF)
        putchar(a);
    putchar('\n');
    // 문자 입력후 '엔터' 치면서 버퍼에 남아버린 개행 문자 제거
    while (getchar() != '\n');  


    // gets와(fgets) puts : 문자열을 받거나 출력
    printf("문자열 입력: ");
    char b[50];
    // gets(b); //! 보안상 이유(buffer overflow) 로 C11부터 제거됨.
    fgets(b, sizeof(b), stdin);
    puts(b);


    // scanf와 printf : 다양한 타입을 입력받고 출력함; 가장많이 사용.
    //format: %s문자열 %c문자 %d정수 %u양의정수 %f실수 %0.3f소수점 반올림
    printf("scanf를 통한 문자열 입력: ");
    char str[50];
    scanf("%s", str);
    printf("%s\n", str);

    int num;
    printf("정수 입력: ");
    scanf("%d", &num);      // 배열, 포인터가 아닌경우 참조자
    printf("%d\n", num);

    float pi = 3.141592;
    printf("%0.3f\n", pi);

    return 0;
}