#include <iostream>
// using namespace std;         //cout을 std:: 없이 쓸수있음.(비추)


// namespace는 함수를 묶어주는 디렉토리로 이해하면 편함.
namespace A {
    void function() {
        std::cout << "Hello!\n";
    }
}

namespace B {
    void function() {
        std::cout << "Wassup!!\n";
    }
}

int main() {
    int favorite_number;
    A::function();
    B::function();
    int age;
    float height = 180.5;
    std::cout << "How old are you? :";
    std::cin >> age;
    std::cout << "you are " << age << " years old. " << height << "cm" << std::endl;
    std::cout << "Enter your favorite num between 1 to 100: ";
    std::cin >> favorite_number;
    std::cout << "That's my fav num too!" << std::endl;

    return 0;
}

