#include "argvtoarray.h"
#include "bubble.h"
#include "printarray.h"
#include "doubleChecker.h"

int main (int argc, char* argv[]) {
    if (!check(argc, argv)) {
        printf("[ERROR]\n");
        return -1;
    }

    double* arr = argvToDoubleArray(argc, argv);
    const unsigned sz = argc - 1;
    printDoubleArray(arr, sz);

    sort(arr, sz);
    printDoubleArray(arr, sz);
    free(arr);

    return 0;
}