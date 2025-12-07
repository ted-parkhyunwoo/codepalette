#include <stdio.h>
#include <stdlib.h>

struct point {
    int x;
    int y;
};

struct rect {
    struct point p1;
    struct point p2;
    
};

int main(void) {

    struct rect r;
    int w, h, area, peri;

    printf("좌측 상단의 좌표 : ");
    scanf("%d %d", &r.p1.x, &r.p1.y);
    printf("우측 하단의 좌표 : ");
    scanf("%d %d", &r.p2.x, &r.p2.y);

    w = r.p1.x - r.p2.x;
    h = r.p1.y - r.p2.y;
    area = abs(w * h);
    peri = abs(2 * (w + h));
    printf("area : %d   peri : %d", area, peri);

    return 0;
}