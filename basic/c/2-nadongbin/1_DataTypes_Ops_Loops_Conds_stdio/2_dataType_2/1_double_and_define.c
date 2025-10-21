#include <stdio.h>
#define MONTHS 12       //상수 정의방법.

int main(void)
{
    double monthSalary = 1000.5;
    printf("$ %.2f", monthSalary * MONTHS); //봉급(변수) * 개월(상수)

    return 0;
}
