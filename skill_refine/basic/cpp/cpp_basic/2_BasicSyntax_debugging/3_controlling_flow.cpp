#include <iostream>


int main() {
    // 조건문
    // if-else, switch-case, ?:
    int num = 1;
    if (num > 1) {
        num+=1;
        int a = 1;      //지역변수.{ } 블록 안에서(if문 외에도) 선언하면 안에서만 접근 가능.
    }                   // 메인함수 바깥에 선언되는 전역변수도 따지고보면 마찬가지.

    // 정수형 리터럴만 사용 가능. (정수,char,열거형)
    switch (num) {
        case 1: break;
        default: break;
    }

    //! 삼항연산 (조건) ? 참일때: 거짓일때;     (간단한 if문 대용.)
    int a = 10;
    int b = 20;
    int result = 0;    result = (a > b) ? (a++) : (b--);  //a보다 b가 크면 a를 저장. 거짓이면 b 저장.


    // 반복문.
    // for (초기화; 반복조건; 증감) {명령문;}    
    for (int i=0; i<5; i++) { } // i는 for()에 생성됐지만 {}안에 넣은것처럼 끝나면사라짐.
    for (; true; ) { break;}    //for문 무한 돌릴 때.

    int i = 0;
    while (i < 5){
        i++;
    }

    bool _is_done = false;
    while(!_is_done) {
        _is_done= true;
    }

    do{break;} while(true);
    // continue 와 break. 

    return 0;
}