#include "Person.h"

// cpp소스: 헤더포함(include), 함수구현, 선언된 메서드 정의

Person::Person() : name("Unknown"), age(0) {
}

std::string Person::getInfo() {
    return "Name: " + name + ", Age: " + std::to_string(age);
}

void Person::setInfo(std::string name, int age) {
    this->name = name;
    this->age = age;
}

