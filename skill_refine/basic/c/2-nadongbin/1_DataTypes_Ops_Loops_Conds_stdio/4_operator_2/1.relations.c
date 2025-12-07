#include <stdio.h>


int main(void)
{
    int x = 50, y = 30;
    // ==는 같다의 의미. = 는 넣는다의 의미
    printf("x == y? %d\n", x == y);    //False를 의미하는 0.
    printf("x != y? %d\n", x != y);    //True를 의미하는 1.
    printf("x > y? %d\n", x > y);
    printf("x < y? %d\n", x < y);
    printf("x = y? %d\n", x = y);       //x를 출력함. 근데 x에 y를 넣음.
    if (x == y)
    {
        //참이면 실행되는 부분
    }
    else
    {
        //if문에 들어온 곳이 거짓 경우 실행되는 부분
    }

    return 0;
}
