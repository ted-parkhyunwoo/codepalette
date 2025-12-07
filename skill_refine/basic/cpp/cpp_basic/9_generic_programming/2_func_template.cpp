#include <iostream>


// 탬플릿으로 T를 타입으로 정의.
template <typename T> // 혹은 U로 많이 씀
T max (T a, T b) {
    return (a > b) ? a : b;
}

// 사용자 정의 클래스(타입) 도 탬플릿 적용 가능. (복습으로 연산자 오버로딩.)
class MyType {
private:
    int user_int;
public:
    MyType(): user_int(0){}
    MyType(int user): user_int(user){};

    friend std::ostream& operator<<(std::ostream& os, const MyType& data) {
        os << data.user_int;
        return os;
    }


    bool operator>(const MyType& compare) {
        return (this->user_int > compare.user_int);
    }

    
};


int main() {

    int a = 10;
    int b{20};

    // 사용시는 max<자료형>(a, b)  으로 써야 함. (컴파일러가 추론 가능하면 안써도 되긴함)
    std::cout << max<int>(a, b) << std::endl;

    // 다른 자료형끼리는 사용이 안됨.
    // std::cout << max(a, 2.5) << std::endl;
    
    // 사용자 정의 타입. 
    // 주의- max<MyType>(m1, m2) 만 썼을때 연산자오버로딩 operator> 가 작성 안된경우에도 컴파일 하기 전까지 오류 출력 하지 않음.
    MyType m1;
    MyType m2{10};
    std::cout << max<MyType>(m1, m2) << std::endl;
    

    //! 타입을 안적어도 기본적으로 추론해서 씀.(권장X)
    std::cout << max(a,b) << std::endl;
    

    return 0;
}
