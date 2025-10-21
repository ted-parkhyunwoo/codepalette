#include <iostream>


int main() {

    // 표현식
    30;
    50;
    20*3;

    //statements : 명령문. 명령수행하는 코드 단위, ;로 종료시킴. 표현식의 집합.
    int favorite_num;
    favorite_num = 20;

    //operations: 연산자. 
    //단항(unary), 이항(binary), 삼항(ternary) 연산자
    // 피연산자 2개 = 이항연산자. 1+3  +는 이항연산자
    // ++a  단항연산자
    // (a)?b:c   삼항. 일단 보류함.

    // 대입연산자 '='
    int num = 0;
    num = 1;
    // 1 = num;     //1이란 '리터럴'은 대입이 안됨. 상수와 리터럴은 대입 할 수 없음.

    // 산술연산자 +, -, *, /, %
    // 증감연산자 ++, --
    // 비교연산자 ==, !=    결과는 true/false
    // 관계연산자 <, >,  <= >=
    // 논리연산자 !, && , ||

    // 논리연산자 팁. short-circuit evaluation
    //컴퓨터는 앞에서부터 논리연산을 보기때문에 
    //!false 가능성 높은것을 앞에 두어야 자원을 아낌.
    if (num == 1 && favorite_num > 21) {}

    // 복합연산자 += %= *= 등. 추가로  <<= >>= &=

    return 0;
}