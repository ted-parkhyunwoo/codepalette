#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {

    int i, x, y;
    int* *pptr = malloc(sizeof(int*) * 8); 

    for (i = 0; i < 8; i++) {
        *(pptr + i ) = malloc(sizeof(int) * 6 );
    }

    for (y = 0; y < 8; y++) {
        for (x = 0; x < 6; x++){
            pptr[y][x] = 6 * y + x;
            // *(*(pptr + y) + x) = (6* y+x);
        }
    }

    for (y = 0; y < 8; y++) {
        for (x = 0; x < 6; x++){
            // printf("%2d ", pptr[y][x]);
            printf("%2d ", *(*(pptr+y)+x));
        }
        printf("\n");
    }




    for (i = 0; i < 8; i++) {
        free(*(pptr + i ));
    }

    free(pptr);


    

    return 0;
}
