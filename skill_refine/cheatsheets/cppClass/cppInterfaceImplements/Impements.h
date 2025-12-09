#include "Interface.h"
#include <iostream>

// 구현클래스
class Implements : public Interface {
    private:
        int userID;

    public:

        Implements(int id) : userID{id} {}

        void sayHello() override {
            std::cout << "Hello " << this->userID << std::endl;
        }

        // 추상클래스 외 새 함수를 정의할 수 있음.(다만 Base참조시 사용불가)
        int getDays() {
            return this->DAYS;
        }
};