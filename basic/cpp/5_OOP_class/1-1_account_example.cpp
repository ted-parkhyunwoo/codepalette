#include <iostream>

class Account {

    std::string name;
    double balance;

    bool Withdraw(double amount);
    bool Deposit(double amount);
};

int main() {

    Account KimsangchulAccount;
    Account YoohyereeAccount;

    Account* ParktedAccount = new Account();
    

    // 객체포인터.
    // (*ParktedAccount).balance = 2;
    // ParktedAccount->balance;



    delete ParktedAccount;
}