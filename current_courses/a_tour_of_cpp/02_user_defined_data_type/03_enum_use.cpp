#include <iostream>

// 일반열거체
enum NormalEnum { red, orange, yellow, green, blue, darkblue = 10, purple };
// class열거체
enum class Colors { red, yellow, green};


//!열거체는 기본기능 구현이 없기 때문에, 필요에 따라서 연산자 오버로딩함.
Colors& operator++(Colors& t) {     // ++i 처럼 전위증가.
    // 증가만 하는게 아니라 루프돌림. ++green -> red
    switch(t) {
        case Colors::red: return t=Colors::yellow;
        case Colors::yellow: return t=Colors::green;
        case Colors::green: return t=Colors::red;   
    }
    return t; // 모든경우에서 반환값이 보장되지 않기때문에 추가했으나, 없어도됨
}

// 후위증가예제. 내부에 전위증가가 있으므로, 따로 루프돌릴 필요없음.
Colors operator++(Colors& t, int) { //! 후위 연산자오버로딩 표기법 Colors& 함수가 아님을 주의. int는 의미없음. 그저 컴파일러가 전위,후위증가 구분을 위한 관습일 뿐.
    Colors old = t; // 현재 값을 저장
    ++t;            // 전위 연산자를 호출하여 값을 증가
    return old;     // 증가 전의 값을 반환
}

// 아웃스트림 오버로딩.
std::ostream& operator<<(std::ostream& os, Colors color) {
    switch (color) {
        case Colors::red: os << "red"; break;
        case Colors::yellow: os << "yellow"; break;
        case Colors::green: os << "green"; break;
    }
    return os;
}

int main() {
    // 일반열거체의 사용.
    NormalEnum res = red;
    std::cout << res << '\n';

    res = purple;
    // res = 2;                 // 사용불가. res는 자료형이 NormalEnum이며 int형이 아니다.
    int res_i = res;            // 사용 가능. res는 int를 return하므로 이렇게는 사용가능.

    std::cout << res << '\n';           // 직접출력 가능.


    // enum class 의 사용.
    Colors res2 = Colors::red;          // red가 여러개일때 명시적으로만 사용 가능하게 함.
    

    // 사용가능한 것들.
    auto res3 = Colors::green;
    Colors res4{2};

    /* 사용 불가능
    int a = Colors::red;
    Colors b = 3;
    std::cout << res2 << '\n';           // 원칙적으로 직접출력 불가
    << 오버로딩 작성하면 가능은 함.(위 operator<< 오버로딩 함수 참고)    

    마찬가지로 ++도 오버로딩 가능.

    */
   std::cout << res2 << '\n';
   std::cout << ++res2 << std::endl;
   std::cout << res2++ << std::endl;
   std::cout << res2 << std::endl;
    return 0;
}