#include <stdio.h>

void print(int count){
    if (count == 0) {
        return;
    } else {
        printf("문자열출력.\n");
        print(count -1);    //!이렇게 재귀사용.
    }
}

int main(void){

    printf("print how much? : ");
    int input_num;
    scanf("%d", &input_num);
    print(input_num);
    
    return 0;
}