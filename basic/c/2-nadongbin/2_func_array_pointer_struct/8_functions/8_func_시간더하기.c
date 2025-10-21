#include <stdio.h>

//전역 변수
int hour;
int minute;
int minuteAdd;

//반환형, 함수이름, 매개변수 세가지로 함수 선언 (리턴이 필요없으면 void)
void counter(){
    minute += minuteAdd;
    hour += minute / 60;
    minute %= 60;
    hour %= 24;
}   

int main(void){
    printf("시를 입력 : ");
    scanf("%d", &hour);
    printf("분을 입력 : ");
    scanf("%d", &minute);
    printf("더할 분을 입력 : ");
    scanf("%d", &minuteAdd);
    counter();
    printf("더해진 결고는 %d시 %d분 입니다.\n", hour, minute);

    return 0;
}
