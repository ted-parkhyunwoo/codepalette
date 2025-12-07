#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 매개변수가 없는 함수와 함수포인터(함수 외 다른매개변수 없음)
void hello() { printf("Hello\n"); }
void bye() { printf("Bye\n"); }
void print(void(*fn)()) {
    printf("RES: ");
    fn();
}

// 매개변수가 있는 함수와 그것을 다루는 함수포인터(함수 외에도 다른 매개변수가 있음-선택)
void hello_name(char* name) { printf("Hello %s\n", name); }
void bye_name(char* name) { printf("Bye %s\n", name); }
void print2(void(*fn) (char*), char* name) {
    printf("RES: ");
    fn(name);
}



int main(int argc, char* argv[]) {

    print(hello);
    print(bye);

    char* name = malloc(1 * 255);
    strncpy(name, "Ted", 3);

    print2(hello_name, name);
    print2(bye_name, name);

    free(name);

    return 0;
}