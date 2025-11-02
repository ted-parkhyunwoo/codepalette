#include <iostream>

// 3 번 예제와 다르게, 동적할당 했으니, 아래와 같이 멤버변수의 동적할당과 초기화를 공부해 둘 것.
// 주요 개념 -> 복사생성자도 생성자다. 생성자의 매개변수를 객체로 받는 생성자일 뿐.

class Base {
protected:
    int* x = new int;
public:
    Base(): x(new int(0)) {
        std::cout << "BASE의 기본 생성자." << std::endl;
    }
    Base(int x) {
        this->x = new int(x);
        std::cout << "BASE의 생성자 - 매개변수받음. x: " << *this->x <<std::endl;
    }

    // 기본클래스 복사생성자. (Base 안에 매개변수를 받는 생성자를 재활용.)
    // [중요] 현재 이 복사생성자는 [인자]를 [객체]로 받는 [생성자]임.
    Base(const Base& source): Base(*source.x) {
        std::cout << "Base 복사 생성자." << *this->x << std::endl;
    }

    ~Base() {
        std::cout << "BASE의 소멸자." << std::endl;
        delete x;
    }
};


class Derived : public Base {
private:
    int* y = new int;
public:
    Derived(): Base() {
        std::cout << "Derived 기본 생성자." << std::endl;
    }

    Derived(int u_input): Base(u_input), y(new int(u_input* 2)) {
        // *this->x = x;
        std::cout << "Derived 생성자 - 매개변수받음. x: " << *this->y << std::endl;
    }


    // 유도클래스의 복사생성자. Base에 넘겨주는 요소를 주목. (Base 의 복사생성자를 호출하게됨.)
    // 객체를 인자로 받는 생성자가 복사생성자 개념인데, Base(객체) 를 사용함으로 Base클래스의 객체로 인자를 받는 생성자(Base의 복사생성자) 를 자동 호출함.
    Derived(const Derived& source): Base(source), y(new int(*source.y)) {
        std::cout << "Derived 복사 생성자." << *this->y << std::endl;
    }
    ~Derived() {
        std::cout << "Derived 소멸자." << std::endl;
        delete y;
    }
};

int main() {
    Derived a(3);
    Derived b{a};           //b의 매개변수로 a라는 객체를 넣었으므로, 복사생성자 호출됨.
    return 0;
}
