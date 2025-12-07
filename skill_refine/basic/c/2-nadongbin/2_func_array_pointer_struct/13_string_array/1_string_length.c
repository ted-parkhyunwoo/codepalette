#include <stdio.h>

int main(void){
    char input[1001];
    // gets(input);
    // gets는 이제 쓰지않음.
    fgets(input, sizeof(input), stdin);
    int counter = 0;


    //! 문자열어레이의 빈공간은 NULL ('\0') 로 채워진다.
    while (input[counter] != '\0') {
        counter++;
    }
    printf("length = %d\n", counter);
    printf("Your input : %s", input);
    return 0;
}