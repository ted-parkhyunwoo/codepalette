#include <stdio.h>
#include <stdlib.h>


// 논리비트. 실제 차지하는 물리공간은 더 큼. 
// TODO 실제로 4비트만 쓰는 방법에 대해 찾아볼 것.
typedef struct BC {
    unsigned int a:1;
    unsigned int b:1;
    unsigned int c:1;
    unsigned int d:1;
} BC;

static BC mybit;

void clearBC() {
    mybit.a = 0;
    mybit.b = 0;
    mybit.c = 0;
    mybit.d = 0;
}

int forBitStrChecker(char* num) {
    for (int i = 0; i < 4; i++) {
        if (num[i] - '0' > 1 || num[i] - '0' < 0) return 0;
    }
    return 1;
}

void initBC(char* num) {
    if (!forBitStrChecker(num)) {
        printf("[ERR]Init fail %s\n", num);
        return;
    }
    mybit.a = num[0] - '0';
    mybit.b = num[1] - '0';
    mybit.c = num[2] - '0';
    mybit.d = num[3] - '0';
}

void printBC() {
    printf("%d%d%d%d\n", mybit.a, mybit.b, mybit.c, mybit.d);
}

char* getBitStr() {
    static char tmp[5];
    tmp[0] = mybit.a + '0';
    tmp[1] = mybit.b + '0';
    tmp[2] = mybit.c + '0';
    tmp[3] = mybit.d + '0';
    tmp[4] = '\0';
    return tmp;
}

int main(int argc, char* argv[]) {
    printBC();

    clearBC();
    printBC();

    initBC("1011");
    printBC();

    char* usrBit = malloc(5);
    printf("bit: ");
    scanf("%s", usrBit);
    initBC(usrBit);
    printf("res: ");
    printBC(usrBit);
    free(usrBit);

    printf("getBitStr(): %s\n", getBitStr());


    return 0;
}