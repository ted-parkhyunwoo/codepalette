#include <stdio.h>
#include <stdlib.h>
#include "./test.h"



int main(int argc, char* argv[]) {
    
    printf("data1: %d\n", data1);
    for (int i = 0; i < 5; ++i) {
        printf("data2: %d\n", data2[i]);
    }

    Struct1 st1;
    st1.value1 = 1000;
    st1.value2 = 2000;
    printf("st1.value1 : %d\n", st1.value1);
    printf("st1.value2 : %d\n", st1.value2);

    printf("DATA3: %d\n", DATA3);
    printf("DATA4: %d\n", DATA4);

    // 컴파일시 gcc main.c test.c
    func1();
    return 0;
}