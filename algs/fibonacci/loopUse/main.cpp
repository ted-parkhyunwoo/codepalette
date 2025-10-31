#include <iostream>
#include "fib.h"

int main() {
    for (int i = 0; i < 100; ++i) {
        std::cout << i << ": " << getFib(i) << std::endl;
    }
    return 0;
}
