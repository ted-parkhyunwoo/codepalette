#include <stdio.h>


int main(void)
{
    int x = 50, y = 30;
    printf("x > y and y < 40? %d\n", (x > y) && (y < 40));  // and 연산은 &&
    printf("x < y or y == 30? %d\n", (x < y) || (y == 30)); // or 연산은 ||
    printf("x is not 50? %d\n", x != 50);       // not은 !=

    return 0;
}
