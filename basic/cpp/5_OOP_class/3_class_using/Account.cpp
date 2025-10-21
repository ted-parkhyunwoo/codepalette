// Account.cpp

#include "Account.h"
#include <iostream>

bool Account::Deposit(double amount){
    balance += amount;
    return true;
}

void Account::Write_Name(std::string username){
    name = username;
    std::cout << username << " Created." << std::endl;
}
