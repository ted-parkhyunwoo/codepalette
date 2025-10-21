#include <iostream>


int add_numbers(int, int);// 프로토타입에는 int, int 이렇게 적어도됨
double add_numbers(double a, double b);
//! 함수는 컴파일러가 int add_numbers(int, int) 통째로 인식함.
//! 따라서 같은이름이래도 자료형이 다르면 중복사용 가능.

//!반환 타입에 따르는 구분은 못함.
/* 이런건 구분할 수 없음.-함수오버로딩 아님.
int get_value();
double get_value();
*/

int main() {
    std::cout << add_numbers(10, 20);
    std::cout << add_numbers(10.0, 20.1);
    //! 컴파일러가 알아서 double인지 int인지 사용함

    return 0;
}

int add_numbers(int a, int b) { 
    return a+b;
}

double add_numbers(double a, double b) { 
    return a+b;
}
