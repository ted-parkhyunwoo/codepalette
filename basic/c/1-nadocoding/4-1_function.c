#include <stdio.h>

//함수의 선언과 정의는 메인함수 앞뒤로 적는다.
//함수의 선언 
void p(int num);

int main(void)
{
    int user_input = 2;
    printf("num 은 %d 입니다\n", user_input);

    user_input += 3;
    p(user_input);     //함수로 대체


    return 0;
}


//함수의 정의.
void p(int num)
{
    printf("num 은 %d 입니다\n" , num);
}


/*
return값이 없을땐 void로 씀 (위와같이.)
float 나 double 등으로 쓰면 return num + 4; 이런식으로 사용

float name(num)
{
    return num + 4;
}

쉽게말해 전체적인 틀은 
반환형 함수이름(전달값)
{
    return 리턴값;
}


함수의 종류

반환값이 없는 함수.
void function_without_return(); //선언
정의에선 
void function_without_return()
{
    printf("반환값이 없는 함수 입니다.\n");
}

반환값이 있는 함수.
int ret = function_with_return();
p(ret);

전달값(파라미터) 가 없는 함수는 ()로 씀
위의 사례와 같음. 

전달 값이 있는 경우
void function_with_parameters(int num1, int num2, int num3); //선언
function_with_parameters(1, 2, 3);  //사용
void function_with_parameters(int num1, int num2, int num3); //정의
{
    printf("%d %d %d", num1, num2, num3);
}
*/
