#include <iostream>

// 상속시에는 생성자.소멸자 들이 직접 상속되진 않음. 멤버함수.멤버변수,상수등만 상속.
// 상속 대신 자녀(파생)클래스가 부모(기본)클래스의 생성자/소멸자를 호출함.
class Base {
protected:
	int x;
public:
	Base()
	: x{0} {
		std::cout << "BASE의 기본 생성자." << std::endl;
	}
	Base(int x) {
		this->x = x;
		std::cout << "BASE의 기본 생성자 - 오버로딩 x: " << x <<std::endl;
	}

	~Base() {
		std::cout << "BASE의 소멸자." << std::endl;
	}

};


class Derived : public Base {
private:
	int test;
public:
	Derived(): Base() {		// 기본과 유도클래스 둘다 비어있는 형태의 생성자 사용시.
		std::cout << "Derived 기본 생성자." << std::endl;
	}

	/* 중요! Derived 생성자에서 인자를 받느냐 안받느냐 에 따라 호출되는 생성자가 다른 것 처럼 
	어떻게 호출하느냐에 따라 Base에서 생성자가 선택됨. 
	Base()로 할지 Base(int x)로 할지 등.
	: Base(x) 로 하면 Base(int x) 로 되고 :Base() 로 하면 Base() 생성자가 호출됨 
	 */
	Derived(int x): Base(x), test{ x* 2} {	// 각기 넣을 수도 있음. x 대신 다른값도 당연히 됨.
	//초기화 리스트를 Base로 적용 가능. Base{x}도 기능상 동일작동. (효율적!)
		// Base::x = this->x; 	// 위 초기화 리스트는 삭제하고 사용. (기본생성자에 직접 대입.비효율적.)
		test = x;
		std::cout << "Derived 기본 생성자 - 오버로딩 x: " << x << std::endl;
	}
	
	~Derived() {
		std::cout << "Derived 소멸자." << std::endl;
	}

};

int main() {

	Derived a{3};

	return 0;
}