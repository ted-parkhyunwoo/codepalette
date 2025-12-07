#include <iostream>

//! 현재 강의는 기본적인 변수선언, namespace의 사용에 관한 것만 알면 됨. class는 임의로 추가한 내용이니 무시해도 됨.

namespace TEST {

    class myclass {
        public:
        void sayhello() {
            std::cout << "TEST -> class -> HELLO!" << std::endl;
        };

    };

    void simplehello() {
        std::cout << "TEST -> SIMPLE HELLO" << std::endl;
    }
}

class myclass {
    public:
    void sayhello() {
        std::cout << "myclass -> HELLO!" << std::endl;
    }
};

int main() {
    myclass A;
    A.sayhello();

    TEST::myclass B;
    B.sayhello();

    TEST::simplehello();

    std::cout << sizeof(int) << std::endl;
    std::cout << sizeof(double) << std::endl;
    std::cout << sizeof(short) << std::endl;

    short a = 32767; // C++에서 short 타입의 허용 범위는 -32,768에서 32,767까지입니다. 이 범위는 2바이트(16비트)로 표현할 수 있는 정수의 범위입니다
    std::cout << a; 


    return 0;
}