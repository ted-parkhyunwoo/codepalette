#include <iostream>
/*  복사생성자에 대해 헷갈릴 때 참고. 아래 설명 주석을 보지 않고, 코드만 읽을 시에는 주석의 번호 순서대로 보면 됨. 

코드의 기본 동작.
NumClass의 멤버변수 num은 그저 포인터이며, 생성자에서 받은 number를 힙공간에 할당해 num에게 주소만 가르쳐줄 뿐임.

문제발생 이유: 
조건1. 생성자의 힙공간 할당 때문에, 소멸자 작성해야함 (delete num). 또한 int* num = new int; 처럼 멤버변수를 선언하고, 생성자에서 *num = number; 처럼 사용할 때도 마찬가지.
조건2. a 객체는 {3} 으로 생성, b 객체는 a로 사용할 때. (NumClass a = {3}; NumClass b = a;)

결과:
결과1. a객체의 num 값과 b 객체의 num 값이 포인터이므로 같은 힙공간의 주소를 포인팅함.  (얕은복사 실행됨.)
결과2. 힙공간 해제를 위해 소멸자 작동시, a는 정상 소멸 되지만, b는 해제한걸 또 하려 하면서 코어 덤프. (얕은복사의 문제점.)

해결:
복사생성 할 때만 새로 힙공간에 다시 num을 넣도록 복사생성자를 다음과 같이 작성. (깊은복사 실행.)
따라서 복사생성자 사용시 a객체와 b객체를 복사생성 하더라도, 독립적인 heap공간을 할당해 소멸자 호출이 원활해짐.

*/
class NumClass {
private:
    // 1. 멤버변수를 힙공간 할당. (그저 생성자에서 할당된 힙주소를 포인팅.)
    int* num;

    // 간단한 예로 int* num = new int{3}; 처럼 int* 로 선언해야 동적할당이 제대로 이루어짐.

public:
    NumClass(int number) {
        // 2. 매개변수를 힙공간에 할당하고 멤버변수로 포인팅.
        num = new int;
        *num = number;
        // num = new int(number);   
        // 별개 이야기로 위 2줄과 사실상 같음. 따라서 멤버함수 선언시 int* num = new int; 후, 생성자에서 *num = number;로 해도 같음.
    }

    // 5. 복사생성자 선언 방법을 따라 작성. (이 복사생성자를 주석처리 해 보면, 소멸자 호출시 코어 덤프됨.(이미 a객체 소멸시 지워진 값을 b가 다시 지우려함))
    NumClass(const NumClass& source) {  // 복사생성자: 매개변수 상수선언, 클래스 자체(데이터타입) 을 역참조. 
        // 6. num을 새로 동적할당한 값으로 원본 클래스의 변수를 포인팅 
        num = new int {*source.num};
    }

    // 7, 복사생성자도 5처럼 안하고, 초기화 리스트로 값을 넣을 수 있음.
    // NumClass(const NumClass& source) NumClass(*source.num) {}

    // 3. 객체가 사라질 때 힙공간 해제를 위해 소멸자 작성.
    ~NumClass() {
        delete num;
    }

    void PrintNum() {
        std::cout << *num << std::endl;
    }
    
};

int main() {
    int test = 3;
    NumClass a = {test};
    // 4. b객체는 a객체를 복사생성. (5번의 복사생성자가 없다면, 멤버변수 num 은 a, b 객체 둘다 같은 주소값을 포인팅함.)
    NumClass b = a;
    a.PrintNum();
    test  = 4;
    b.PrintNum();

    return 0;
}