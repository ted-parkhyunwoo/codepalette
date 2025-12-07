#include <stdio.h>
#include <stdlib.h>

// 다양한 타입 사용 가능. (그저 컴파일러에게 코드 변경을 요청하는 복사붙여넣기에 가까움 : 컴파일 타임 전에 전처리됨.)
#define DATA1 100
#define DATA2 "안녕하세요\n"
// 상수의 의미로 대문자로 하는것이 관례.

int main(int argc, char* argv[]) {
    
    // 1. const는 메모리 수정을 막음
    const int a1 = 1000;
    printf("a1 : %d\n", a1);
    
    // error.
    // a1 = 2000;
    printf("a1 : %d\n", a1);

    // 2. 전처리 명령어 define은 컴파일시 코드가 대체됨. 메모리공간을 사용하지 않고 컴파일시점에 정함.
    printf("DATA1 : %d\n", DATA1);
    printf("DATA2 : %s\n", DATA2);

    return 0;
}