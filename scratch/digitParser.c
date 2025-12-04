#include <stdlib.h>
#include <stdio.h>


// arg: string -> boolean
int isDigitString(char* str) {
    while (*str != '\0') {
        if (*str < '0' || *str > '9') return 0;
        ++str;
    }
    return 1;
}

// test isDigitString
void _testIsDigitString() {
    char* test[] = {"123", "asdf", "as09", "husda", "0234892", "3.14"};
    for (int i = 0; i < (sizeof(test) / sizeof(char*)); ++i) 
        printf("[isdigit test log] %s: \t%s\n", test[i], isDigitString(test[i])? "true" : "false");
}

// string -> int
int stoi(char* str) {
    // 변환할 수 없는 string까지 처리하는 atoi 확장판
    if (isDigitString(str)) return atoi(str);
    printf("err: %s is not a integer.\n", str);
    return 0;
}

// test stoi
void _testStoi() {
    char* test[] = {"123", "asdf", "as09", "husda", "0234892", "3.14"};
    for (int i = 0; i < (sizeof(test) / sizeof(char*)); ++i) {
        int token = stoi(test[i]);
        printf("[strToInt test log] %s -> \t(int) %d\n", test[i], token);
    }
}


int main(int argc, char* argv[]) {
    
    _testIsDigitString();
    _testStoi();

    return 0;
}