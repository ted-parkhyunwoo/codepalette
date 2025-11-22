#include "Person.h"

//! 소스코드에는 override임을 명시하면 컴파일 오류나는 경우가 있음. 필요시 헤더에만 할 것.
void Person::setInfo(std::string name, int age) {
    this->name = name;
    this->age = age;
}

std::string Person::getInfo() {
    return "Name: " + this->name + " age: " + std::to_string(this->age);
};

Person::~Person() {}