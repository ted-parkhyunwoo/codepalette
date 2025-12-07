#include <iostream>

class a {
    public:
    void Talk() {
        std::cout << "Hello" << std::endl;
    }
};

class b: public a {
    public:

    // 정적바인딩. 객체의 클래스 우선으로(타입을 기준으로) 컴파일러가 실행.
    void Talk() {
        std::cout << "Hello World!" << std::endl;
    }

    // 오버라이드
    void TalkA() {
        a::Talk();
    }
};
int main() {

    a A;
    A.Talk();

    b B;
    B.Talk();


    // 복사대입. 
    // 이상해 보이지만, 객체 복사대입시, B의 멤버변수만 A 에 복사하는 과정임. (멤버함수는 x)
    // 따라서 A = B를 해도, b클래스가 아니라 a 클래스의 Talk() 가 호출 됨.
    A = B;
    A.Talk();

    // 클래스 포인터도 마찬가지로 a의 타입으로 생성했기 때문에, a.Talk()가 실행됨.    
    a *TEST = new b;        //a 타입을 b 타입으로 초기화가 가능하단 점에 주목. 인자를 받는 클래스라면 new b{1}; 이런식으로 초기화함.
    TEST->Talk();

    a& TEST2 = B;
    TEST2.Talk();
    
    //오버라이드
    B.TalkA();

    return 0;
}