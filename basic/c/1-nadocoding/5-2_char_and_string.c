#include <stdio.h>

int main(void)
{

    // 문자 vs 문자열
    char c = 'A';       //주의!! 작은따옴표.
    printf("%c\n", c);
                           
    // 문자열을 프린트 할 때 문자열의 끝을 의미하는 \0을 넣는다! \0은 NULL 문자. 
    // char str[6] = "coding";  // [c] [o] [d] [i] [n] [g] 
    // char str[7] = "coding";  // [c] [o] [d] [i] [n] [g] [\0] <- 하나 더 넣으면 이것이 자동으로 들어감
    char str[] = "coding";   // 이것도 저절로 7로 맞춰지면서 \0을 자동으로 채움.
    // char str[7] = { 'c', 'o', 'd', 'i', 'n', 'g', '\0' };       //사실 이것과 같음.
                                                            

    printf("%c\n", str[1]);     //문자열이니 인덱스로 한글자 추출도 가능.
    printf("%s\n", str);  //현재 터미널엔 문제 없어보이나, 그냥 쓰면 안됨.
    printf("%d\n", sizeof(str));        //사이즈를 출력 할 때 씀.

    // 한국어 문자열의 크기.
    char kor[] = "나도코딩";
    printf("%s\n", kor);
    printf("%d\n", sizeof(kor));
    // 영어1글자 : 1byte
    // 한글1글자 : 2byte    //EUC-KR, CP949 기준, 현재 UTF-8은 3바이트.
    // char 크기 : 1byte
    

    // 나머지는 NULL로 채워짐.
    char c_array[10] = { 'c', 'o', 'd', 'i', 'n', 'g'};     // "coding"; 로 해도 같음.
    for (int i = 0; i < sizeof(c_array); i++)
    {
        printf("%c\n", c_array[i]);
        printf("%d d로 하면 ascii로 나옵니다.\n", c_array[i]);
    }

    // 이렇든 문자열은 항상 여유를 주고 하면 문제는 안생김


    return 0;
}
