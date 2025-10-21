#include <stdio.h>

int main(void)

{
    char x = 'A';   // char는 ascii의 int(65)를 A로 변환하는점 숙지. 'A' 말고 65로 넣어도 같음.
    printf("%c\n", x);    //int로 바꿔도 %c로 출력하면 'A' 로 나옴.
    int y = 65;
    printf("%c\n", y);
    int z = 66;
    printf("%c\n", z);  
    return 0;
}
