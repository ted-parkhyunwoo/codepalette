#pragma once
#include <ctype.h>
#include <string.h>

int isDouble(const char* str) {
    const unsigned sz = strlen(str);
    for (unsigned i = 0; i < sz; i++) {
        if (i == 0) {
            if (!(isdigit(str[i]) || str[i] == '-'))
                return 0;
        }
        else if (!(isdigit(str[i]) || str[i] == '.'))
            return 0;
    }
    return 1;
}


int check(const int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        const char* token = argv[i];
        if (!isDouble(token))
            return 0;
    }
    return 1;
}