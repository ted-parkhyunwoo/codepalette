#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//객체지향 클래스의 근본이 구조체.
//서로 다른 자료형을 묶어서 처리하는 개념.

struct point {
    int x;
    int y;
};


int main(void) {

    struct point p1, p2;
    int xDiff, yDiff;

    double distance;

    printf("First Point : ");
    scanf("%d %d", &p1.x, &p1.y);

    printf("Second Point : ");
    scanf("%d %d", &p2.x, &p2.y);

    xDiff = p1.x - p2.x;
    yDiff = p1.y - p2.y;

    // 거리 = (x차이제곱 + y차이제곱)제곱근
    distance = sqrt(xDiff * xDiff + yDiff * yDiff);
    
    printf("points distance : %f\n", distance);

    return 0;
}