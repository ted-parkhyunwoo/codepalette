// 함수 stack memery로 scope 영향 없이 값을 변경하는 array 외에 reference(참조자: &기호) 가 있다. 배열과 포인터가 아닌경우에도 가능.

#include <iostream>

void change(int& num) { 
    //!포인터랑 다르게 메모리의 주소값도 가지지 않음. 따라서 아무 값도 저장하지 않고 곧바로 매개변수(여기선 number)의 값을 포인팅 함. (number의 별명을 부여하는 느낌.)
    num += 1;
}

int main() {
    int number = 1000;

    std::cout << number << std::endl;
    change(number);
    std::cout << number << std::endl;

}

//! 추가첨언 - 참조자 & 는 메모리를 복사하지 않으므로, 자원 절약(메모리)에 도움이 되나, 직접적인 값 수정을 할 수 있으므로 주의해서 사용.
