//! 클래스헤더는 명세만 하고 구현은 동일명.cpp로 하는 것이 관습.

// 전처리기 헤더 다중포함 제거후 한번만 컴파일 하게 하는 지시문
#pragma once

// // 이전의 전통적인 전처리기 지시문 (인클루드 가드.)
// #ifndef EXAMPLE_H
// #define EXAMPLE_H
// // ---내용---
// #endif

#include <string>
class Account {

public:
    //클래스 헤더에는 프로토타입 선언
    bool Withdraw(double amount);
    bool Deposit(double amount);
    void Write_Name(std::string username);

private:
    std::string name;
    double balance;

};