#include <iostream>
#include <ostream>

// 사용자 정의 타입 배열의 [] 를 index로 작동하게 하는 과정.
// 6번 문서와 같은 내용이므로, 첨자연산자(subscript operator) 오버로딩은 GetValue 멤버함수 부터 보면 됨.


class MyArray {
private:
    int* anArray;
    int aSize;
public:
    // init object from null data.
    MyArray() {
        aSize = 1;
        anArray = new int[aSize];
        anArray[0] = {'\0'};    //NULL
    }

    // 시작 정수 st와 size를 입력하여 초기화 생성자
    MyArray(int st, int sz): aSize{sz} {
        anArray = new int[aSize];
        for (int i = 0; i < aSize; i++) {
            anArray[i] = st + i;
        }
    }

    // DEEP COPY copy constructor
    MyArray(const MyArray& obj) {
        anArray = new int[obj.aSize];
        aSize = obj.aSize;
        for (int i = 0; i < aSize; i++) {
            anArray[i] = obj.anArray[0] + i;
        }
    }

    // destructor. - delete heap memory link
    ~MyArray() {
        delete[] anArray;
    }


    // << operator overload for ostream.
    friend std::ostream& operator<<(std::ostream& os, const MyArray& obj)
    {
        os << "[";

        for (int i = 0; i < obj.aSize; i++) {
            os << obj.anArray[i];
            if (i != obj.aSize - 1) os << ", ";
        }

        os << "]";

        return os;
    }


    // return obj for copy init. 
    MyArray& operator=(const MyArray& obj) {
        // fast return. must check that is same obj. (prevent delete anArray)
        // MyArray a{st, sz}; a = a; work.
        if (this == &obj) return *this;

        delete[] anArray;
        aSize = obj.aSize;
        anArray = new int[obj.aSize];
        for (int i = 0; i < obj.aSize; i++) {
            anArray[i] = obj.anArray[i];
        }
        return *this;
    }

    // 인덱스 출력시 예제.

    //  anArray의 범위 밖도 출력되므로, 정상적인 코드가 아님.
    void GetValue(int index) {
        std::cout << anArray[index];   
    }

    // 참조자로 리턴해야 값변경도 가능
    int& operator[](int index) {

        // 조기 종료(1코드) + 오류출력문.
        if (index < 0 || index >= aSize) {
            std::cout << "Out of range." << std::endl;
            exit(1);
        }

        return anArray[index];
    }

    // 참조자 없이 const로 상수 오버로딩 해야 const 선언된 객체 값 변경 불가. 
    // 위 함수에서 const 키워드만 넣으면 const 선언된 객체인데도 값이 변경됨. 따라서 첨자연산자 오버로딩은 두개를 같이 작성해줘야 함.
    int operator[](int index) const {

        // 조기 종료(1코드) + 오류출력문.
        if (index < 0 || index >= aSize) {
            std::cout << "Out of range." << std::endl;
            exit(1);
        }

        return anArray[index];
    }

};


int main() {

    MyArray a{1,5};
    std::cout << a << std::endl;
    // operator<<(std::cout, a);    와 같음.

    std::cout << a[4] << std::endl; // a[0] = a.operator[](0)

    a[0] = 3;
    std::cout << a << std::endl; 


    // 상수선언시 값 변경 불가처리.
    const MyArray b{1, 2};
    std::cout << b;
    // const 는 값 변경 불가하게 하기 위해 오버로딩 해야함.(두개구현)
    // b[0] = 2;
    std::cout << b;

    return 0;
}

