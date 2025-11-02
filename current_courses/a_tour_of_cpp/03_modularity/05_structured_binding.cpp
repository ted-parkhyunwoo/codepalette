#include <iostream>
#include <tuple>
#include <map>

// 구조적바인딩(structured binding)은 C++17에서 도입된 기능. unpack 개념임. (복사가 거의 일어나지 않음)

struct Person {
    std::string name;
    int age;
    double height;
};

//! 교재에 없는내용: 구조적 바인딩 !아님! 주의. 매개변수에 풀어 넣을 때. js의 ... 이나 파이썬의 *args:튜플, **kwargs:딕셔너리 보다는 기능들이 좀 한정적임.
// 따라서 필요에 따라 차선책이 필요함.  아래 템플릿 가변인자 사용 외 std::tuple 과 std::apply의 조합으로 매개변수를 전달 가능: 이것은 구조적 바인딩으로도 가능.
template<typename... Args>                  //템플릿 가변 인자 ... Args 사용: 마찬가지로 볷사가 거의 일어나지 않음.
void printValues(Args... args) {
    ((std::cout << args << " "), ...);      //전개 연산
}


int main() {
    printValues(1, 2, 3, 4, 5);  // 1 2 3 4 5

    // 구조적 바인딩으로 구조체 분해
    Person person{"Alice", 30, 165.5};
    auto [name, age, height] = person;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Height: " << height << " cm" << std::endl;


    // 구조적 바인딩으로 튜플 분해
    std::tuple<int, double, std::string> myTuple{1, 3.14, "Hello"};
    auto [integerPart, doublePart, stringPart] = myTuple;
    std::cout << "Integer: " << integerPart << std::endl;
    std::cout << "Double: " << doublePart << std::endl;
    std::cout << "String: " << stringPart << std::endl;


    // std::map 생성 및 초기화
    std::map<std::string, int> myMap = {
        {"Apple", 3},
        {"Banana", 5},
        {"Cherry", 8}
    };

    // 구조적 바인딩을 활용한 for문 순회
    for (const auto [key, value] : myMap) {
        std::cout << "Key: " << key << ", Value: " << value << std::endl;
    }


    
    return 0;
}