//! 2-1의 문제를 Deep copy로 해결. - 나중문제지만, STL, smart pointer등을 사용할 수도 있음.
#include <iostream>

class Deep {
private:
    int* data;

public:
    Deep() = default;
    Deep(int d);    //프로토 타입. (포인터 사용중.)
    Deep(const Deep& source);   //!복사생성자 프로토 타입.
    ~Deep();

    void Print() {
        std::cout << *data << std::endl;
    }
};

//클래스에 대한 멤버 함수는 class 내부에 프로토타입이 작성 됐다면 아래와 같이 바깥에 적어도 되니, 헷갈리지 말 것.

Deep::Deep(int d) {
    data = new int;
    *data = d;
}

Deep::~Deep() {
    delete data;
    std::cout << "free storage" << std::endl;
}


//! 복사생성자 예1). const와 역참조 & 를 사용.
Deep::Deep(const Deep& source) {
    data = new int {*source.data}; //! deepcopy 예시의 핵심. 새로운 heap할당.
    std::cout << "Copy constructor used." << std::endl;
}

//! deep copy 예2) 복사생성자도 생성자라서 멤버 초기화 리스트로 만들 수도 있음. 현재 위임시킬 생성자 Deep(int d) 는 data를 새로 heap에 할당하여 넣기 때문에 깊은 복사가 일어남.

// Deep::Deep(const Deep& source) : Deep(*source.data) { std::cout << "Copy constructor used." << std::endl; }


void DisplayDeep(Deep obj) {
    obj.Print();
}

int main() {
    Deep a = {3};
    a.Print();
    DisplayDeep(a);
    a.Print();      // 모두 정상작동하고, 사용 후 소멸자 실행하여 소멸시킴.

    Deep b = {a};   //이렇게 할 때도 복사생성자 작동.
    b.Print();

    // Deep c;
    // c = b;  //이 때는 복사생성자 작동 안함. 오류로 주석처리.(복사가 아니라 대입.)

    //간단한 예
    int* ptr1 = new int {300};
    int* ptr2 = new int {*ptr1};    //heap에 ptr1값을 복사생성.
    std::cout << *ptr1;
    std::cout << *ptr2;
    delete ptr1;
    delete ptr2;        

    return 0;
}