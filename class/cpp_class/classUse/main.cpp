#include <iostream>
#include "Person.h"

// h,cpp분리 이유: 코드 재사용성 향상, 컴파일시간 단축, 인터페이스,구현분리, 캡슐화


int main() {
    Person* p = new Person();

    p->setInfo("ted", 32);
    std::cout << p->getInfo() << std::endl;

    delete p;
    return 0;
}