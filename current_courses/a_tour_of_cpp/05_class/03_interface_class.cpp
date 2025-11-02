#include <iostream>
#include <sstream>

//! 인터페이스클래스 (추상클래스, 다형타입 등으로도 불림)
class Container {
    public:
        //! 추상타입의 '일반적인' 특징으로 !!생성자를 포함하지 않음!!
        // 이유: (어떠한 데이터도 초기화하지 않음. 객체를 초기화하지 않음-> 호출될일이 없음.)
        virtual double& operator[](int) = 0;        // 순수 가상함수: virtual, =0; 으로 만들며, 반드시 구현해야함.
        virtual int size() const = 0;
        virtual ~Container() {}                     // 일반 가상함수(소멸자) : 반드시 구현을 강요하진 않음.
        // 소멸자는 보통 순수가상함수로 작성하진 않음
        // 이유: 소멸자를 필요로 하지 않는 (즉 직접 구현없이 암묵적구현)만으로도 충분한 구현클래스들도 인터페이스를 사용하기 위함.
};

// 최소한의 실수형 배열 구현타입:  인터페이스 클래스:다형클래스(Container) 상속받음.
class Vector : public Container {   //! : public 은 ~에서 파생된, ~의 하위타입이라 읽음(스트롭스트룹)
    private:
        double* data;
        int sz;
    public:
        Vector(int size) : sz(size), data(new double[size]) {
            for (int i = 0; i < size; ++i) data[i] = 0;
        }

        // 사실 override 키워드는 생략 가능하나, 추상타입을 따르고있다는 의도를 명확하게 하기 위함.
        //! 정확히는 철자 오류, 타입 차이 등을 컴파일러가 잡아내기 쉬워짐.
        double& operator[](int index) override { return data[index]; }  
        int size() const override { return sz; }
        ~Vector() { delete[] data; }
};


// 인터페이스타입을 함수로 사용시:
void printArray(Container& c) {
    std::ostringstream oss;
    oss << '[' << c[0];
    for (int i = 1; i < c.size(); i++) {
        oss << ", " << c[i];
    }
    oss << ']';
    std::cout << oss.str() << std::endl;
}

int main() {

    //! 추상타입은 포인터, 참조로 쓰이는게 일반적임.
    // 포인터 사용
    Container* myArray = new Vector(5);

    // 참조자 사용
    Vector myVec(3);
    Container& myArray_ref = myVec;

    // 함수사용
    myVec[0] = 1;
    myVec[1] = 2;
    myVec[2] = 3;
    printArray(myVec);
    
    //! 추상타입은 직접사용 불가: 추상클래스의 객체는 존재하지 않음.
    // Container myArray2 = Vector(3);
    // Container myArray3;

    return 0;
}