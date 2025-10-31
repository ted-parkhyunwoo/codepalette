#include <iostream>
#include "fibonacci.h"

int main(int argc, char* argv[]) {
    if (argc < 2) return -1;
    char* arg = argv[1];
    std::string argStr(arg);
    int n = 0;
    try {
        n = std::stoi(argStr);
    } catch (const std::exception& e) {
        std::cerr << "Invalid number." << std::endl;
        return -1;
    }

    if (n < 0 || n > 92) {
        std::cerr << "0 <= n <= 92" << std::endl;
        return -1;
    }

    initMemo(++n);
    for (int i = 0; i < n; ++i) {
        std::cout << i << ": " << getFib(i) << std::endl;
    }
    freeMemo();

    return 0;
} 
