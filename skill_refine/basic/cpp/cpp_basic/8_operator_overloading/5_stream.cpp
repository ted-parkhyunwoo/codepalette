#include <cmath>
#include <iostream>


// 간략하게 iostream - ostream - cout(전역 객체) 구조임.
// iostream - istream - cin 도 마찬가지.

// cout<< (데이터) 는 operator<<(os객체-즉 cout, 데이터) 형식의 함수로 실행. 타입은 수많은 오버로딩으로 정의됨.(int, double 등등.)
// std::ostream& operator<<(std::ostream& os, const MyClass& obj) 이 함수를 컴파일러가 찾는다는 뜻. (os객체는 즉 cout.)
// std::cout<<"test"; 이 것은 operator<<(std::cout, "test"); 와 동일.
// 따라서 사용자 정의 타입에 스트림 삽입, 추출을 사용하기 위한 연산자 오버로딩.



class MyOstream {
public:
    void operator<<(int user_value) {
        printf("%d", user_value);
    }
};

class Position {
private:
    int xpos;
    int ypos;
public:
    Position(int user_xpos, int user_ypos): xpos(user_xpos), ypos(user_ypos) {};


    // out stream 삽입 구현. (전역함수. ostream 객체 반환.)
    // 참조자를 주목할 것. cout객체는 복사생성 사용 불가.
    friend std::ostream& operator<<(std::ostream& os, const Position& obj) {
        os << "[" << obj.xpos << "," << obj.ypos << "]";
        return os;
    }


    /*
    // 이렇게 사용하면, 연속으로 스트림 삽입이 불가.(단독사용은 가능.) 위 코드를 자세히 보면 왜 연속삽입이 가능한지 알 수 있음.(cout클래스 객체에 출력 값을 추가를 하여 리턴되는게 연쇄적으로 일어남.)
    (void, obj) << std::endl; 즉 operator<<(void, obj) 로 작동되므로 사용불가.

    friend void operator<<(std::ostream& os, const Position& obj) {
        os << "[" << obj.xpos << "," << obj.ypos << "]";
    }

    */


    // 스트림 추출 구현;
    // Position객체의 좌표를 변경하므로 const 아님에 주의.
    friend std::istream& operator>>(std::istream& is, Position& obj) {
        int new_x;
        int new_y;
        is >> new_x >> new_y;
        obj.xpos = new_x;
        obj.ypos = new_y;
        //혹은 obj = Position{new_x, new_y}; 
        return is;
    }


    // 별개로, 비트시프트. (스트림 삽입과 기호는 같으나 역할은 다름.)
    Position operator<<(int shift) {
        return Position((xpos<<shift), (ypos<<shift));
    }

    Position operator>>(int shift) {
        return Position((xpos>>shift), (ypos>>shift));
    }

}; 



int main() {
    // cout 과 같은 구현.
    std::cout << "cout 직접 구현" << std::endl;

    MyOstream test;
    test.operator<<(1);
    test << 2; // 다른 이항연산자와 같음 결국.
    std::cout << 3;
    puts("");


    std::cout << "스트림삽입" << std::endl;

    // cout객체 생성후 직접 함수 호출시.
    std::ostream& asdf = std::cout;
    operator<<(asdf, "test");

    puts("");



    // out스트림 삽입 연산자 오버로딩의 구현. 
    Position a{3,4};
    std::cout << a << std::endl;
    // std::cout << a   =   operator<<(cout, obj)
    // cout도 ostream의 객체임. ostream& os    
    // class ostream {};
    // ostream cout;(전역 객체.) 이런 형태로 정의되어 있음을 염두하면 이해하기 쉬움.
    // 참고. 전역객체 namespace std { extern ostream cout;}



    // istream, 스트림 삽입예제.
    puts("스트림추출");
    Position cinTest{0,0};
    Position cinTest2{1,1};
    std::cout << "입력: ";
    std::cin >> cinTest >> cinTest2; // 연속추출 1 2 3 4 가능.
    // operator>>(std::cin, cinTest); 와 같음.
    // operator>>(istream클래스의 cin 객체(전역객체), obj)
    std::cout << cinTest << cinTest2 << std::endl;




    // 이하 마음대로 작성한 부분.
    puts("동적할당");
    const Position* b = new Position{7,7};
    std::cout << *b << std::endl;
    delete  b;

    b = &a;
    operator<<(std::cout, *b);
    operator<<(std::cout, "\n");

    puts("bitshift");


    // bit shift <<, >> operator overloading
    Position d{2,3};
    std::cout << d << std::endl;
    d = d << 1;
    std::cout << d << std::endl;
    d = d >> 1;
    std::cout << d << std::endl;


    return 0;
}