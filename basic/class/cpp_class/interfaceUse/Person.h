#pragma once
#include <iostream>
#include "IPerson.h"

class Person : public IPerson {
    private:
        std::string name;
        int age;
    public:
        //! 헤더에는 override임을 명시할 수 있음(강제아님)
        void setInfo(std::string name, int age) override;
        std::string getInfo() override;
        ~Person() override;
};