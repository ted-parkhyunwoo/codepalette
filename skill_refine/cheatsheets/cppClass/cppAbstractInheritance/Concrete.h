
#include <iostream>
#include "Abstract.h"

// 구체클래스: 일부 행동만 구현시
class Concrete: public Abstract {
    std::string name;

    public: 
        // 생성자는 추상클래스를 그대로 호출
        Concrete(int id, std::string name) : Abstract(id), name{name} {}

        void sayHello() override {
            std::cout << "Hello user " << this->userId <<  ". your name is " << this->name << ".\n";
        }
};