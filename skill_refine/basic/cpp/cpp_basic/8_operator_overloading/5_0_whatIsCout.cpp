#include <iostream>
#include <ostream>

int main() {
    // std::ostream 객체를 참조하는 변수 선언
    std::ostream& asdf = std::cout;
    // cout은 ostreamd의 객체.
    
    // << 는 비트시프트 연산자 이지만, cout 혹은 cin의 객체에서는 이미 오버로드 되어 다르게 사용됨.  예 ) operator<<(std::ostream&, {type} 변수이름);

    // 객체(std::cout)<< {something}; 으로 << 연산자가 스트림삽입(ostream) 으로 작동하는 원리. 
    // 이전에 객체 + 객체 혹은 객체 + int 등 오버로딩 했듯이, cout 객체 << {something} 은 something 에 수많은 데이터 타입이 오버로딩 되어 있다.



    // 직접 operator<< 호출
    // 수많은 오버로딩이 작성 되어, std::string 형태로 입력된거도 알아서 출력됨.
    operator<<(asdf, "test");

    // 스트림 연속 삽입.
    asdf<< "Hello World" << std::endl;
    return 0;
}

