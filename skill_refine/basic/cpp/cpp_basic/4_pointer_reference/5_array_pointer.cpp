#include <iostream>

int main() {
    int scores[] = {100, 95, 90};
    std::cout << scores << std::endl;
    std::cout << *scores << std::endl;
    std::cout << scores[0] << std::endl;
    std::cout << sizeof(scores) << std::endl;
    

    int* scores_ptr = scores;
    std::cout << scores_ptr << std::endl;
    std::cout << *scores_ptr << std::endl;    
    std::cout << scores_ptr[0] << std::endl;
    std::cout << sizeof(scores_ptr) << std::endl;
    // 포인터라 사이즈는 다름 (64비트라 8바이트. 32비트 컴퓨터는 4바이트)

    int num = 10;
    scores_ptr = &num;  // 포인터라서 어레이 대신 그냥 int도 사용가능.
    std::cout << *scores_ptr << std::endl;
    // scores = &num;   // 비슷하지만, 어레이에선 이런 사용이 안됨.

    // scores[0] = num;     // 이런 식으로 사용함.
    std::cout << *scores << std::endl;

    return 0;
}