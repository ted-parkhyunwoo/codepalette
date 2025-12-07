#include <stdio.h>
#include <math.h>   // pow()
#include <stdlib.h>      // abs() 사용을 위해. 
                    // 거듭제곱, 절대값


int main(void)
{   
    double z = pow(2.0, 20.0);  //2.0 밑, 20.0 지수
    printf("2의 20제곱은 %.0f입니다. \n", z);
    
    int x = 20, y = -30;
    printf("x와 y의 차이 : %d\n", (abs(x - y)));
    printf("y와 x의 차이 : %d\n", (abs(y - x)));
    return 0;
}
