#include <math.h>
#include <stdio.h>

//! compile: gcc roundDouble.c -std=c17 -lm -O3 -o ./test.out
/*
    일부 간단한 pow 나 round는 실질적인 pow나 round 호출 없이 gcc가 최적화 처리 해버림.
    그래서 때때로, main함수 내에선 작동할 때가 있음.
    식을 조금 복잡하게 만들면 math.h가 실제로 필요하기 때문에, -lm 을 사용해야함.
*/


double roundDouble(double origin, int digit) {
    double p = pow(10, digit);
    return round(origin * p) / p;
}

int main() {
    double pi = 3.14159265358979;

    // 출력으로 반올림
    {
        // 원본이 잘림
        printf("%f\n", pi);
        // 원본 손상없이 출력시도
        printf("%.14f\n", pi);
        // 출력으로 반올림
        printf("%.6f\n", pi);
    }


    // 실제 실수변수를 반올림하여 저장하는 트릭(round활용)
    {
        // 소수점 2자리까지.
        double piCp = round(pi * 100) / 100;
        printf("%f\n", piCp);

        // 6자리까지
        piCp = round(pi * 1000000) / 1000000;
        printf("%.f\n", piCp);        // 기본 %f는 소수점 6자리까지 출력됨

        // 8자리까지
        piCp = round(pi * 100000000) / 100000000;
        printf("%.8f\n", piCp);
    }

    // 함수화 시도
    {
        double test = roundDouble(pi, 6);
        printf("%6f\n", test);

        test = roundDouble(pi, 2);
        printf("%6f\n", test);
    }




    return 0;
}