#include <iostream>

#include "Account.h"

int main() {

    Account park;

    //멤버함수 사용예제.
    park.Write_Name("Tedpark");
    if (park.Deposit(100) != false) {
        std::cout << "Deposit successful." << std::endl;
    } else {
        std::cout << "[ERROR] Deposit Fail." << std::endl;
    }




    return 0;
}