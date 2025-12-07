#pragma once
#include <time.h>
#include <iostream>

class Dice {
    private:
        int count[6];
    public:
        static int getDice();
        Dice();
        void print();
        void plusElement(int n);
        void roll(long n);
};


Dice::Dice() {
    srand(time(NULL));
    for (int i = 0; i < 6; ++i) count[i] = 0;    
}

void Dice::print() {
    for (int i = 0; i < 6; ++i)
        std::cout << i + 1 << ": " << count[i] << "\n";
}

void Dice::plusElement(int n)   { count[n - 1]++; }

int Dice::getDice()             { return (rand() % 6) + 1; }

void Dice::roll(long n) {
    for (long i = 0; i < n; ++i)
        this->count[getDice() - 1]++;
}