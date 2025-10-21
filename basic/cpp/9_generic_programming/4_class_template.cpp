#include <iostream>

template<typename T>
class Item{
private:
    std::string name;
    T value;
    
public:
    Item(std::string user_name, T user_value) : name{user_name}, value{user_value} {}
    std::string getName() { return name; }
    T getValue() { return value; }
};

// 특수화 (더블로 value를 받으면 2배로 리턴하도록 하는 예제). Item<double> 로 작성해야함.
template<>
class Item<double>{
private:
    std::string name;
    double value;
    
public:
    Item(std::string user_name, double user_value) : name{user_name}, value{user_value} {}
    std::string getName() { return name; }
    double getValue() { return 2 * value; }
};


// 다중매개변수
template<typename T1, typename T2>
class NewItem{
private:
    T1 name;
    T2 value;
    
public:
    NewItem(T1 user_name, T2 user_value) : name{user_name}, value{user_value} {}
    T1 getName() { return name; }
    T2 getValue() { return value; }
};

int main() {
    // 컴파일러가 템플릿을 기준으로 int형과 double형을 취하는 각 두가지 클래스를 만듬.
    // 이 클래스는 각각 다름.

    // <타입> 을 명시하지 않으면 템플릿 함수와는 다르게 템플릿 클래스는 추론되지 않음.(c++17 이상에선 자동으로 됨)
    Item<int> i{"hello", 10};
    std::cout << i.getName() << "," << i.getValue() << std::endl;
    
    Item<float> j{"HELLO", 3.141592};
    std::cout << j.getName() << "," << j.getValue() << std::endl;
    
    // 위에 설명한대로 타입명시하지 않아도 c++17로 컴파일로 실행하면 정상작동함
    // 컴파일 옵션에 "-std=c++17" 를 추가하면 작동은 정상적으로 됨.
    // vscode의 경우 Win32에 cpp는 c++17로 추가해 줘야 함. (코드검사기)
    Item k{"heLlO", 3}; //당연히 어느 환경에서나 컴파일 되게 하기 위해서는 권장하지 않음.


    // 다중 매개변수도 다중타입 사용 가능. 
    NewItem<std::string, int> a{"A", 3};
    std::cout << a.getName() << "," << a.getValue() << std::endl;
    // c++17 에선 타입 명시 하지 않아도 알아서 추론함.
    NewItem b{3,"test"};
    std::cout << b.getName() << "," << b.getValue() << std::endl;

    // 특수화- 더블로 입력시 2배로 리턴. (Item<double> 로 쓰는게 정석. )
    Item c{"C", 3.14};
    std::cout << c.getName() << "," << c.getValue() << std::endl;

    
    return 0;
}