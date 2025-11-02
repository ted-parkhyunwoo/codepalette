#include <iostream>

class MyClass {
    protected: 
        int x;
    public:
        MyClass(int x) : x{x} {}
        MyClass() { this->x = 0; }

        // <=> 우주선 연산자 오버로딩: 3자간 비교로, a = b : 0, a < b : -1, a > b : 1 세가지로 출력됨.
        //! 우주선연산자를 오버로딩하면(직접구현) 나머지 관계연산자도 암묵적으로 자동 정의됨!! (==, != 제외.)
        auto operator<=>(MyClass& b) {
            std::cout << "우주선연산자 호출" << std::endl;
            return (this->x == b.getValue()? 0 : this->x < b.getValue()? -1 : 1); 
        }

        int getValue() {
            return x;
        }
        void print() {
            std::cout << x << std::endl;
        }
};

// == 비교연산자 오버로딩. 올바른 평가를 위해 보통 클래스 바깥에서 비교.
bool operator==(MyClass& a, MyClass& b) {
    return a.getValue() == b.getValue();
}

// =! 비교연산자 오버로딩. 자동으로 생성되지 않으며, == 를 구현하면 !(비교식) 으로 쉽게 구현가능하다.
bool operator!=(MyClass& a, MyClass& b) {
    return !(a.getValue() == b.getValue());
}




int main() {
    MyClass a;
    a.print();
    MyClass b(1);
    b.print();

    //! < 를 구현한적 없는데도 우주선연산자를 구현해서 호출된다.
    std::string res = a < b ? "true" : "false";
    std::cout << res << std::endl;
    return 0;
}