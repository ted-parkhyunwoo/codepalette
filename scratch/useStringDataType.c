#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    //! 계속 사용 가능한 String의 예. (입력되는 string의 길이 필요에따라 realloc 됨) - 사용자 입력의 string 예제임에 주의.

    int idx = 0;
    int capacity = 10;
    int capaStep = 10;
    char* userStr = malloc(sizeof(char) * capacity);

    while(1) {
        int bf = getchar();

        if (bf == EOF) {
            
            idx = 0;
            free(userStr);
            capacity = capaStep;
            userStr = malloc(sizeof(char) * capacity);
            idx = 0;
            *userStr = '\0';
            break;
        }
        
        if (capacity - 1 == idx) {
            capacity += capaStep;
            userStr = realloc(userStr, capacity);
        }
        userStr[idx] = bf;
        idx++;

        if (bf == '\n') {
            userStr[idx] = '\0';
            break;
        }
    }

    
    printf("idx: %d\n", idx);
    printf("capacity: %d\n", capacity);
    printf("strlen: %zu\n", strlen(userStr));
    printf("userStr: %s\n", userStr);

    free(userStr);
    



    /*
    
    char* testStr1 = "abc";
    char testStr2[] = "abc";
    char* testStr3 = malloc(sizeof(char) * 20);
    char testStr4[20];

    *testStr3 = '\0';
    *testStr4 = '\0';
    printf("%s\n%s\n%s\n%s\n\n", testStr1, testStr2, testStr3, testStr4);


    testStr1 = "bcd";
    // strcpy(testStr1, "123");     //! 불가
    printf("%s\n", testStr1);
    // scanf("%s", testStr1);       //! 불가


    
    // testStr2 = "bcd";            //! 불가
    strcpy(testStr2, "bcd");
    printf("%s\n", testStr2);
    printf("input: ");
    scanf("%s", testStr2);          //* 처음 선언된 str의 길이와 정확히 일치해야만 가능
    printf("%s\n", testStr2);
    

    printf("input: ");
    scanf("%s", testStr3);
    printf("%s\n", testStr3);
    free(testStr3);


    printf("input: ");
    scanf("%s", testStr4);  
    printf("%s\n", testStr4);

    
    */
    return 0;
}