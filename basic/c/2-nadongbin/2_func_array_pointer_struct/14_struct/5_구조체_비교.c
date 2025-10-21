#include <stdio.h>

struct point {
    int x;
    int y;
};

void comparePoint (struct point p1, struct point p2){
    if ((p1.x == p2.x) && (p1.y == p2.y)){
        printf("p1 과 p2가 같습니다");
    }
}


int main(void){
    struct point p1;
    struct point p2;

    p1.x = 30;
    p1.y = 10;

    p2.x = 30;
    p2.y = 10;

    // 이렇게 직접비교는 오류남.
    // if (p1 == p2){
    //     printf("p1 eqauls p2 \n");
    // }

    // comparePoint함수처럼 비교해야함. (구조체 멤버라 함. 멤버가 같다.). //!메인함수 내부에서도 작동하나, 함수구현함.
    // 파이썬의 클래스 내부에선 어트리뷰츠라 하는데 그것과 비슷한 느낌.
    comparePoint(p1, p2);
    
    return 0;
}