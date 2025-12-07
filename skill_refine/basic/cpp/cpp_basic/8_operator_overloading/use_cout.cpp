#include <iostream>
#include <ostream>


int main() {

    // 이상한 문제점. 
    int test = 1;
    std::string test2 = "1";
    operator<<(std::cout, test2);       //std::string은 되나 int는 안됨.
    std::cout.operator<<(test);         //int는 되나 std::string은 안됨.
    std::cout<<std::endl;
    std::cout << test;


    return 0;
}