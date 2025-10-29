#include <stddef.h>
#include <unistd.h>
#include <string.h>

// gcc -shared -o libmylib.so mylib.c

int arraySum(int* arr, size_t size) {
    int res = 0;
    for (size_t i = 0; i < size; ++i) {
        res += *(arr + i);
    }
    return res;
}

void printWelcome(char* name) {
    const char msg[] = "welcome ";
    write(1, msg, 8);       // 표준출력 = 1
    write(1, name, strlen(name));
    write(1, ".\n", 2);
}


