#include <stdio.h>

// 특정한 금액을 받아서 가장 적은 거스름돈 화폐의 개수를 구하는 함수.
void changes(int number){
    int count = 0;
    int money[7] = {0, 0, 0, 0, 0, 0, 0};
    while(number >= 50000){
        number -= 50000;
        money[0]++;
    }
    while(number >= 10000){
        number -= 10000;
        money[1]++;
    }
    while(number >= 5000){
        number -= 5000;
        money[2]++;
    }    
    while(number >= 1000){
        number -= 1000;
        money[3]++;
    }
    while(number >= 500){
        number -= 500;
        money[4]++;
    }    
    while(number >= 100){
        number -= 100;
        money[5]++;
    }
    while(number >= 50){
        number -= 50;
        money[6]++;
    }
    while(number >= 10){
        number -= 10;
        money[7]++;
    }

    int i;
    for (i = 0; i < 7; i++){
        if (money[i] == 0){
            continue;
        }
        switch (i){
            case 0:
                printf("5만원권 : ");
                break;
            case 1:
                printf("1만원권 : ");
                break;
            case 2:
                printf("5천원권 : ");
                break;
            case 3:
                printf("1천원권 : ");
                break;
            case 4:
                printf("500원권 : ");
                break;
            case 5:
                printf("100원권 : ");
                break;
            case 6:
                printf("50원권 : ");
                break;
            case 7:
                printf("10원권 : ");
                break;
        }

        printf("%d개    " , money[i]);
    }
    if (number != 0){
        printf("1원권 : %d개 \n", number);
    }

}

int main(void){
    int number;
    printf("금액 입력 : ");
    scanf("%d", &number);
    //printf("최소로 줄 수 있는 화폐 개수는 %d개 \n", changes(number));
    changes(number);

    return 0;
}
