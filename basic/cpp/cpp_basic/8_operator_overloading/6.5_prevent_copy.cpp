#include <iostream>
#include <ostream>

/*
객체의 복사, 대입을 차단 해야 할 때. 만들지 않아도 기본 복사생성자, 대입연산자 오버로딩이 있으므로,

1. private: 에 빈 함수로 넣음.
2. 혹은 public멤버함수 = delete; --구현하지 않겠다는 의미. (최신)


필요한 이유 - 배열 같은경우는 안정성이 높지 않기 때문에, 복사나 대입을 허용하지 않는 경우가 꽤 있음.
*/

class MyArray {
private:
    int* anArray;
    int aSize;

    // 복사/ 대입 차단 예 1.
    // MyArray(const MyArray& obj){}   // 복사생성
    // MyArray& operator=(const MyArray& obj) {}   //대입연산

public:

    // 복사/ 대입 차단 예 2.   --최신기능.
    MyArray(const MyArray& obj) = delete;
    MyArray& operator=(const MyArray& obj) = delete;


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


};


int main() {
    MyArray a{1,5};
    std::cout << a << std::endl;

    // 복사생성 (불가처리 함.)
    MyArray b = a;
    std::cout << b << std::endl;

    // 대입연산 (불가처리 함.)
    MyArray c;
    c = a;
    std::cout << c << std::endl;


    return 0;
}

