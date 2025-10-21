#include <iostream>
#include <ostream>

class MyArray {
private:
    int* anArray;
    int aSize;
public:
    MyArray() {
        aSize = 1;
        anArray = new int[aSize];
        anArray[0] = {'\0'};    //NULL
    }

    MyArray(int st, int sz): aSize{sz} {
        anArray = new int[aSize];
        for (int i = 0; i < aSize; i++) {
            anArray[i] = st + i;
        }
    }


    MyArray(const MyArray& obj) {
        anArray = new int[obj.aSize];
        aSize = obj.aSize;
        for (int i = 0; i < aSize; i++) {
            anArray[i] = obj.anArray[0] + i;
        }
    }


    ~MyArray() {
        delete[] anArray;
    }

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


    // MyClass 타입으로 반환시.
    MyArray& operator=(const MyArray& obj) {
        // 같은게 맞는지 확인 안하면 해제해버림.
        if (this == &obj) return *this;

        delete[] anArray;
        aSize = obj.aSize;
        // 복사생성사 처럼 anArray를 새로 생성. (먼저 해제 후.)
        anArray = new int[obj.aSize];
        for (int i = 0; i < obj.aSize; i++) {
            anArray[i] = obj.anArray[i];
        }
        
        return *this;
    }


};


int main() {
    MyArray a{1,5};
    std::cout << a << std::endl;

    // 복사생성에는 문제가 없음.(복사생성자를 만든 경우.)
    MyArray b = a;
    std::cout << b << std::endl;

    // 대입연산은 문제가 생김. (복사생성자를 만들어도. =연산자 오버로딩으로 깊은 복사 수행 안하면.)
    MyArray c;
    // c.operator=(a);
    c = a;
    std::cout << c << std::endl;


    // 아무것도 입력 없이 출력 되게 함.
    MyArray d;
    std::cout << d << std::endl;


    // 상수선언도 작동하게 함.
    const MyArray* e = new MyArray{5,10};
    std::cout << *e << std::endl;
    delete e;

    return 0;
}

