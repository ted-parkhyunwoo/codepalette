#include <stdio.h>

int main(void)
{
    int x = 50;
    float y = 123456789.123456789;  
    printf("x = %d\ny = %.2f\n", x, y); //float는 4byte밖에 못써서 다른걸 써야됨.
    double z = 123456789.123456789;     //double은 8byte라서 널널함.
    printf("z = %.2f\n", z);
    printf("z = %.8f\n", z);    //파이썬처럼 부동소수점 처리 문제.
    return 0;
}
