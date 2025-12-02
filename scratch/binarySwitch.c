#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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

void printBin(uint8_t n) {
    char* binString = malloc(sizeof(char) * 9);    // 반전 위해 필요한 공간. string출력을 안하기 때문에 null공간 배제
    
    unsigned binIdx = 0;
    while(n > 0) {
        binString[binIdx++] = (n % 2) + '0';
        n >>= 1;
    }
    for (; binIdx < 8; binIdx++)        binString[binIdx] = '0';
    binString[binIdx] = '\0';

    for (unsigned i = 7; i > 0; i--)   printf("%c", binString[i]);
    printf("%c\n", binString[0]);

    free(binString);
}

int main() {
    uint8_t tmp = 12;

    // 진수표기별 변수 저장
    tmp = 0b1100;   // 2진수 표현(12)
    tmp = 014;      // 8진수 표현(12)
    tmp = 0x000c;   // 16진수표현(아래 모두 12로 같은값)
    tmp = 0xC;
    tmp = 0x0c;
    
    // 진수 출력
    printf("진수출력:\n");

    // 안타깝게도 print format은 2진수 출력 안됨. 8, 16진수는 가능
    printf("10:%d, 8:%o, 16:%x, 16:%X\n", tmp, tmp, tmp, tmp);
    print_uint8_binary(12);     // gemini 구현
    printBin(12);               // 직접 구현 


    // 논리연산자
    printf("논리연산: \n");

    // 논리곱(AND), 논리합(OR), 반전(!기호와 다름. NOT이란 명칭은 같음)
    print_uint8_binary(~0b1010);            // 11110101
    print_uint8_binary(0b1111 & 0b0101);    // 1111 & 0101 -> 0101
    print_uint8_binary(0b0101 | 0b1010);    // 0101 | 1010 -> 1111
    
    // 복합(NAND: NOT AND ~(A & B) , NOR: NOT OR ~(A | B)) 이 있음.

    // bit shift.
    printf("비트시프트:\n");
    print_uint8_binary(0b1010 >> 1);        // 0101
    print_uint8_binary(0b0001 << 1);        // 0010
    // 특징: bitshift 진행시마다 값은 2배 커지거나 2배 나누어짐(나머지 버림 처리)


    // 스위치 제어 예제. mem을 손상하지 않고 res로 업데이트
    printf("논리연산자를 통한 스위치 제어 예제:\n");
    uint8_t mem, mask, res;
    
    mem =  0B00000011;
    mask = 0B00000001;

    // mem에서 mask로 지정된 것이 활성화 되어있는지 검사
    res =  mem & mask;
    printf("활성스위치: ");
    print_uint8_binary(res);        // 00000001

    mem =  0B01010101;
    mask = 0B10101010;

    // 켜기(전에 켜져있든 꺼져있든)
    res = mem | mask;
    printf("켜기 결과: ");
    print_uint8_binary(res);        // 11111111
    
    // 끄기(A & ~B)
    res = res & ~mask;
    printf("끄기 결과: ");
    print_uint8_binary(res);        // 01010101;


	return 0;
}
