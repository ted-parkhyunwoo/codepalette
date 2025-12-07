#pragma once
#include <iostream>
// h파일: 클래스선언, 멤버변수 선언, 함수선언, 상수정의. 
class Person {
    private:
        std::string name;
        int age;
    public:
        Person();
        std::string getInfo();
        void setInfo(std::string name, int age);
        ~Person() = default;        // 컴파일러 기본 제공 소멸자 사용. 이런경우 소스코드에서 구현할 필요 없음.
};