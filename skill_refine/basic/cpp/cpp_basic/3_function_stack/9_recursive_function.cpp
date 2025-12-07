// 팩토리얼 같은 재귀함수 구현시, 재귀호출을 끝내는 return이 들어가지 않으면 stack overflow가 생김.
//이유는 함수를 호출 할 때마다 콜스택을 쌓기 때문.

#include <iostream>

int factorial(int n) {
    if (n == 0)  //! 재귀호출은 base case.(기저조건) 무조건 만들어야함
        return 1;   //없애면 그냥 강제종료됨.
    else
        return n * factorial(n - 1); // 재귀 호출
}

int myStyleFactorial(int n);    //! 내 스타일의 팩토리얼 함수 프로토타입(추가작성)

int main() {
    std::cout << factorial(5) << std::endl;
    std::cout << myStyleFactorial(5) << std::endl;

    return 0;
}


//! 추가 첨언 - 원래 내 코딩 스타일에는 재귀호출을 선호하지 않음. 인라인 함수에 추가첨언 했듯이, 재귀호출은 위험할 수 있는 것이 변수를 콜스택에 복사생성 하기 때문에 자원 사용에 불리함. 만약 사용하더라도 무한 루프에 빠지지 않도록 기저조건을 만들 것. 

int myStyleFactorial(int n) {
    if (n < 0) return -1;
    if (n == 0) return 1;
    
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}