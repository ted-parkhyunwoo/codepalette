#include <stdio.h>
#include <stdlib.h>

/* 다양한 전처리기 명령어: 번호 순으로 읽는 것을 추천한다. */

// 3. 헤더파일 호출(기본형태. 자세한건 다음 강의에 다룸.)
#include "./20_test.h"      

// 1. 상수 선언
#define DATA1 100
#define DATA2 200

/// 8. 함수 호출; 코드대체-copy,paste
#define FN1() printf("FN1 called.\n");
#define FN2(a, b) printf("FN2 called: %d, %d\n", a, b);
// #은 매개변수를 문자열화 한다. \
    FN3예제 주의! ", " 와 "\n" 이지 " #a " 나 " #b " 가 아니다. \
    #a -> "a의 문자열" 형태로 이미 변환됨.
#define FN3(a, b) printf("FN3 called: " #a ", " #b "\n");
// 여러 코드 사용시 한줄로"만" 이어 붙일 수 있으나, 백슬래시 사용으로 여러줄 코드 입력 가능.
#define FN4(a, b) \
    printf("FN4 called:\n"); \
    printf("a: " #a "\n"); \
    printf("b: " #b "\n");


int main(int argc, char* argv[]) {

    // 1. 선언된 상수사용
    printf("DATA1: %d\n", DATA1);       // DATA1, DATA2 는 변수가 아님.(전처리기에서 대체)
    printf("DATA2: %d\n", DATA2);
    int a1 = DATA1 + DATA2;
    printf("DATA1 + DATA2: %d\n", a1);


    // 2. 상수 해제
    #undef DATA1                        
    // printf("DATA1: %d\n", DATA1);        // 오류 발생.


    // 3. 헤더파일 내 함수 호출.
    test1();        


    // 4. ifdef, endif; 전처리기 정의되어 있을 때 코드 흐름 제어
    #ifdef DATA1
    printf("DATA1 정의됨\n");
    #endif

    #ifdef DATA2
    printf("DATA2 정의됨\n");
    #endif


    // 5. ifndef, endif; 정의되어있지 않을 때 코드 흐름 제어
    #ifndef DATA1
    printf("DATA1 정의안됨\n");
    #endif

    #ifndef DATA2
    printf("DATA2 정의안됨\n");
    #endif    


    // 6. #if, #else, #elif     // 조건제어
    #if DATA2 < 200
    printf("DATA2 < 200\n");
    #elif DATA2 == 200
    printf("DATA2 == 200\n");    
    #else
    printf("FALSE\n");
    #endif


    // 7. 미리 define 된 상수들.
    printf("__DATE__ : %s\n", __DATE__);    // 현재 날짜.
    printf("__TIME__ : %s\n", __TIME__);    // 현재 시간
    printf("__FILE__ : %s\n", __FILE__);    // 실행된 파일 이름

    /* windows에선 출력 안되는 상태. */ 
    // printf("__LINE__ : %s\n", __LINE__);    // 이곳이 실행된 코드의 라인번호
    // printf("__STDC__ : %s\n", __STDC__);    // 일반적인 c컴파일러로 컴파일된 경우 1. 아니면 0 리턴


    // 8. 함수호출
    FN1();
    FN2(1, 3);
    FN3(10, 20);
    FN4(10, 20);

    return 0;
}