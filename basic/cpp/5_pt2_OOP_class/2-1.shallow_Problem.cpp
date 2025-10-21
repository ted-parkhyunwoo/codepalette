//! 얕은 복사(shallow copy) 의 문제점. - 변수에 포인터 타입이 있는 경우.


#include <iostream>

class Shallow {
private:
    int* data;  //이것이 문제를 일으킴. 정확히는 객체가 복사되고, 소멸자 작동시 문제됨.

public:
    Shallow(int d);
    Shallow(const Shallow& source);
    ~Shallow();

    void Print() {
        std::cout << *data << std::endl;
    }
};

Shallow::Shallow(int d) {
    data = new int;
    *data = d;
}

Shallow::~Shallow() {
    delete data;
    std::cout << "free storage" << std::endl;
}

// 기본 복사생성자의 형태는 이런식임.
Shallow::Shallow(const Shallow& source) : data(source.data) {
    std::cout << "Copy constructor used." << std::endl;
}

void DisplayShallow(Shallow obj) {
    obj.Print();
}


int main() {
    Shallow a = {3};
    a.Print();
    DisplayShallow(a);  // 이 때, 소멸자 호출로 data가 delete됨. //! 논리오류. 
    a.Print();      // 다시 호출 할 땐, a의 data가 이미 지워진 heap메모리의 값을 포인팅함.

    //간단한 예
    int* ptr1 = new int {300};
    std::cout << *ptr1;
    int* ptr2 = ptr1;
    std::cout << *ptr2;
    delete ptr1;
    delete ptr2;        // 사실상 두번 해제 하는 논리오류. //! 논리오류.

    return 0;
}