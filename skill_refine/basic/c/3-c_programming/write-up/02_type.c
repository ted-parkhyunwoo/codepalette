#include <stdio.h>

int main(int argc, char* argv[]) {

    printf("char: %lu\n", sizeof(char));
    printf("u_char: %lu\n", sizeof(unsigned char));
    printf("s_char: %lu\n\n", sizeof(signed char));

    printf("int : %lu\n", sizeof(int));
    printf("u_int : %lu\n", sizeof(unsigned int));
    printf("short : %lu\n", sizeof(short));
    printf("u_short : %lu\n", sizeof(unsigned short));
    printf("long : %lu\n", sizeof(long));
    printf("u_long : %lu\n\n", sizeof(unsigned long));

    printf("float : %lu\n", sizeof(float));
    printf("double : %lu\n", sizeof(double));
    printf("l_double : %lu\n\n", sizeof(long double));

    printf("char* : %lu\n", sizeof(char*));
    printf("l_double* : %lu\n", sizeof(long double*));
    return 0;
}