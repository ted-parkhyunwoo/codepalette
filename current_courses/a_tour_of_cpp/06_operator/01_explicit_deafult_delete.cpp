#include <iostream>

class Y{
public:
    Y() {};
    //! 암묵적 변환 막음. (보통 1개의 매개변수 입력받는 생성자에서 암묵적 변환이 일어나며, 이것을 의도하지 않은 경우 즉 막아야 할 경우에 사용.) !!!!!한마디로 명시적 호출만 허용한단 뜻.
    explicit Y(int num) : data{num} {};    

    //! default 키워드는 컴파일러가 생성하는 기본생성자, 복사생성자 등을 사용을 명시적으로 함.
    // 복사, 할당 등이 단순한 객체라는 뜻.
    Y(const Y&) = default;      // 복사생성자 (복사초기화)
    Y(Y&&) = default;           // 이동생성자

    //! delete 키워드는 사용하지 않겠다는 의미.(복사대입:복사할당 금지) 
    Y& operator=(const Y&) = delete;

private:
    //! 멤버 초기자 설정해놓으면 생성자에서 초기화리스트(initialize list) 까먹어도 정상작동되고, 코드도 간편해짐.
    int data = 0;    
    int* sz = nullptr;
};

int main() {

    Y a;
    Y b;
    // a = b;          // 복사대입 금지로, 사용불가.
    Y c = a;        // 복사생성은 가능. (복사초기화)
    Y d {a};        // 마찬가지로 복사생성.

    Y e(5);
    // Y f = 5;     // 암묵적 변환 금지해서 안됨.
    std::cout << "실행완료" << std::endl;
    return 0;
}

