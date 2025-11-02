#include <iostream>
#define PI 3.14159
// 전처리기로 PI 를 macro로 작성

// 매크로를 통한 MAX 함수 구현.
/* 복사-붙여넣기 형식이니 괄호를 감싸는 것을 더욱 주의해야 함.
예를들어 3 / SQUARE(2) 가 3/2*2로 작동하게 되는 등 연산자 우선순위 고려, 삼항연산 고려 등 

매크로 사용 지양 이유
1. 디버깅을 할 수 없음.
2. namespace가 없어서 전역범위가 되어버림.
*/
#define MAX(a,b) ((a>b)? a : b)


// 함수 오버로딩을 통한 max 구현.
int max(int a, int b) {
    return (a > b)? a:b;
}
double max(double a, double b) {
    return (a > b) ? a : b;
}


int main(){
    double a = PI * 3;
    double b = PI * 4;

    // int 형태만 사용 가능한 상태.
    std::cout << max(3,4) << std::endl;
    // 함수 오버로딩을 통해 다른 타입을 만들어야만 사용 가능.
    std::cout << max(a,b) << std::endl;



    // 매크로를 사용한 함수구현.
    std::cout << MAX(a,b) << std::endl;
    std::cout << MAX(3, 4) << std::endl;
    // 매크로는 복사-붙여넣기 구조라서 아래와 같은 형태로 변환됨
    std::cout << ((a > b) ? a:b) << std::endl;
    std::cout << ((3 > 4) ? 3:4) << std::endl;

    return 0;
}
