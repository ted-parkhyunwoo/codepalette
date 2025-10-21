#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    char *ptr_array[3] = {
        "asdf",
        "qwer",
        "1234:"
        };

    char ** pptr = ptr_array;
    printf("%s", *(pptr+1));
    
    
    return 0;
}
