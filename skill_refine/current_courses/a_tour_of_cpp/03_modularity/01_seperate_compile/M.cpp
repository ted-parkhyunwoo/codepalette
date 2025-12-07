#include <iostream>
#include "M.h"

Recipe::Recipe(int w, int c) : water{w}, coffee{c} {}

void Recipe::getInfo() {
    std::cout << "water: " << water << "  coffee: " << coffee << std::endl;
}