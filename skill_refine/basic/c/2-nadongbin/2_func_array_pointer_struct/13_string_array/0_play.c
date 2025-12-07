#include <stdio.h>

int main(void){
    //! 널문자(\0)이 마지막에 들어가므로 한칸 늘려야함
    char string[11] = "abcdefghij";
    printf("%s\n", string);
    string[0] = 'A';
    printf("%s\n", string);


    //array 는 사실 포인터.
    char *ptr = string;
    ptr[0] = 'a';
    printf("%s\n", ptr);
    
    *(ptr+1) = 'B';
    printf("%s\n", string);

    //똑같음.ㅋㅋㅋ
    //이래서 string은 자체가 포인터인 것임. (string에 포인터를 쓸 이유가 없는듯.)
    *string = 'A';
    printf("%s\n", string);
    printf("%c\n", *(string+1));


    

    return 0;

}