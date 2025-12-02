#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// 주의: 자료형 선택시 부호 없는 자료형을 사용하는것이 bit shifting, 출력문 등에 문제 발생 여지를 없앨 수 있다.

// gemini 구현
void print_uint8_binary(uint8_t n) {
    // 7번째 비트(MSB)부터 0번째 비트(LSB)까지 반복
    for (int i = 7; i >= 0; i--) {
        // 비트 마스크 생성 (1 << i)를 이용하여 i번째 비트만 1로 만듦
        // n과 마스크를 AND 연산하여 해당 비트가 설정(1)되어 있는지 확인
        if (n & (1 << i)) {
            printf("1"); // 1이면 '1' 출력
        } else {
            printf("0"); // 0이면 '0' 출력
        }
    }
    printf("\n"); // 출력 후 줄 바꿈
}

// 직접구현(메모리 할당/해제 오버헤드 있음)
void printBin2(uint8_t n) {
    char* binString = malloc(sizeof(char) * 9);    // 반전 위해 필요한 공간.
    
    unsigned binIdx = 0;
    while(n > 0) {
        binString[binIdx++] = (n % 2) + '0';
        n >>= 1;
    }
    for (; binIdx < 8; binIdx++)        binString[binIdx] = '0';
    binString[8] = '\0';        // 올바른 free를 위한 널문자 추가.

    // unsigned에 0보다 작아지는 순간 발생할 수 있는 문제 제어 추가된 비트출력
    for (unsigned i = 7; i > 0; i--)    printf("%c", binString[i]);
    printf("%c\n", binString[0]);   

    free(binString);
}

// printBin2 개선을 위해 직접구현 했으나 gemini와 별반 다를게 없어짐.
void printBin(uint8_t n) {
    for (int i = 7; i >= 0; --i)
        // n & (1 << i) 는 정수이며, 결과가 0과 1이 아니라 실제로는 자릿수별 정수값(1, 2, 4, 8...)이 값이 있냐 없냐(0)로 boolean 처리됨에 유의.
        printf("%c", (n & (1 << i))? '1': '0');     
    printf("\n");
}


int main() {
    uint8_t tmp = 12;

    // 진수표기별 변수 저장
    tmp = 0b1100;           // 2진수 표현(12)
    tmp = 014;              // 8진수 표현(12)
    tmp = 0x000c;           // 16진수표현(아래 모두 12로 같은값)
    tmp = 0xC;
    tmp = 0x0c;
    
    // 진수 출력
    printf("\n진수출력:\n");

    // 안타깝게도 print format은 2진수 출력 안됨. 8, 16진수는 가능
    printf("10:%d, 8:%o, 16:%x, 16:%X\n", tmp, tmp, tmp, tmp);
    print_uint8_binary(12);         // gemini 구현
    printBin(12);                   // 직접 구현 


    // 논리연산자
    printf("\n논리연산: \n");

    // 논리곱(AND), 논리합(OR), 반전(!기호와 다름. NOT이란 명칭은 같음)
    printBin(~0b1010);              // 11110101
    printBin(0b1111 & 0b0101);      // 1111 & 0101 -> 0101
    printBin(0b0101 | 0b1010);      // 0101 | 1010 -> 1111
    
    // 복합(NAND: NOT AND ~(A & B) , NOR: NOT OR ~(A | B)) 이 있음.

    // bit shift.
    printf("\n비트시프트:\n");
    printBin(0b1010 >> 1);          // 0101
    printBin(0b0001 << 1);          // 0010
    // 특징: bitshift 진행시마다 값은 2배 커지거나 2배 나누어짐(나머지 버림 처리)


    // 스위치 제어 예제. mem을 손상하지 않고 res로 업데이트
    /* 활용 예: 
        1. 통신 등에 어떠한 입력들(동시)이 있었는지 정수값 하나만 전송하면 빠른속도로 동시입력 전송 가능
        2. 현 상태에 대한 정보를 담을 저장공간(메모리 혹은 디스크공간)을 정수값 하나만 할당하여 저장 가능
    */

    printf("\n논리연산자를 통한 스위치 제어 예제:\n");
    uint8_t mem, mask, res;
    
    mem =  0B00000011;
    mask = 0B00000001;

    // mem에서 mask로 지정된 것이 활성화 되어있는지 검사
    res =  mem & mask;
    printf("\n활성스위치: \t");
    printBin(res);                  // 00000011 & 00000001      ->  00000001

    mem =  0B01010101;
    mask = 0B10101010;


    // 스위치 상태 확인 응용 (8개의 스위치 on/off 검사)
    printf("\n스위치상태: \n");
    uint8_t mySwitch = 0B01010101;
    for (unsigned want_to_see = 0; want_to_see < 8; ++want_to_see) {        // 0 ~ 7. 마지막자리부터 탐색(쉬프트)됨.
        uint8_t isOn = mySwitch & (1 << want_to_see);
        printf("\t%i 번 스위치: %s\n", want_to_see, isOn? "true" : "false");
    }


    // 켜기(전에 켜져있든 꺼져있든)
    res = mem | mask;               // 01010101 | 10101010      ->  11111111
    printf("\n켜기 결과: \t");
    printBin(res);

    // 끄기(A & ~B)
    res &= ~mask;                   // 11111111 & 01010101(~10101010)   ->  01010101    
    printf("끄기 결과: \t");
    printBin(res);


    // XOR 스위치: mask에 1처리된 부분만 토글가능
    mem = 0B00001010;
    mask = 0B00001111;
    res = mem ^ mask;   // 0101: mask에서 1로 처리된 곳만 mem에서 반전
    res = res ^ mask;   // 1010: res 를 다시 반전하여 복구
    printBin(res);


    // XOR 연산 응용: 정수의 tmp, bf 할당 없이 swap처리
    int a = 3;
    int b = 5;
    printf("%d, %d\n", a, b);
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("%d, %d\n", a, b);

	return 0;
}
