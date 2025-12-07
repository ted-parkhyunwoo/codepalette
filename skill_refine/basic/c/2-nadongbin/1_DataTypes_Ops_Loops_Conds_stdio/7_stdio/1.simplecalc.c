#include <stdio.h>

int main(void){

    char o;
    int x, y;
    while(1){
        printf("수식을 입력 : ");
        scanf("%d %c %d", &x, &o, &y);
        if (o == '+'){
            printf("%d %c %d = %d\n", x, o, y, x + y);
        }
        else if (o == '-'){
            printf("%d %c %d = %d\n", x, o, y, x - y);
        }
        else if (o == '-'){
            printf("%d %c %d = %d\n", x, o, y, x - y);
        }
        else if (o == '*'){
            printf("%d %c %d = %d\n", x, o, y, x * y);
        }
        else if (o == '/'){
            printf("%d %c %d = %d\n", x, o, y, x / y);
        }
        else if (o == '%'){
            printf("%d %c %d = %d\n", x, o, y, x % y);
        }
        else {
            printf("invalid input.\n");
        }
        getchar();      //안하면 버퍼(윗줄에 입력한 엔터)때문에 진행 안됨.
        printf("Turn off calculator? (y/n) :");
        scanf("%c", &o);
        if (o == 'y' || o == 'Y'){
            break;
        }
        else {
            continue;
        }

    }


    return 0;
}
