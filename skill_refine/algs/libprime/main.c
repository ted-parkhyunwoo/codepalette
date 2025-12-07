#include "prime.h"

int main() {

    size_t* res = get(100);
    printf("%zu\n", res[0]);
    freeMem(res);

    return 0;
}