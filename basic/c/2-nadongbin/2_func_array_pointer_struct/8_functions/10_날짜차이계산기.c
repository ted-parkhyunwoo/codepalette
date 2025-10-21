#include <stdio.h>

int getDays(int month, int day) {
    int i, sum = 0;
    for (i = 1; i < month; i++) {
        if (i == 2) {
            sum += 28;      //현재 프로그램은 윤년은 감안하지 않습니다. (연도 입력x)
        } else {
            if (i <= 7){
                if (i % 2 == 0) {
                    sum += 30;
                } else {
                    sum += 31;
                }
            } else {
                if (i % 2 != 0) {
                    sum += 30;
                } else{
                    sum += 31;
                }
            }
        }
    }
    return sum + day;
}

int main(void) {
    int month, day;
    printf("몇월 며칠인가요? (띄어쓰기 구분) : ");
    scanf("%d %d", &month, &day);   //해당 일이 30 혹은 31이 넘어도 감안하지 않습니다.
    printf("1월1일부터 %d월%d일 까지 총 %d 일 입니다.",month, day, getDays(month, day));


    return 0;
}
