#include <iostream>
#include "Person.h"

int main() {
    Person p = Person();
    p.setInfo("park", 32);
    std::cout << p.getInfo() << std::endl;
    return 0;
}