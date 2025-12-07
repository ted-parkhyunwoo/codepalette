#include <iostream>

class IPerson {     // I는 인터페이스란 뜻을 가진 관례.
    public:
    virtual void setInfo(std::string name, int age) = 0;
    virtual std::string getInfo() = 0;
    // virtual void nothing() = 0;      // 구현클래스 Person에서 재정의 하지 않으면 컴파일 되지 않음.

    // 인터페이스 소멸자 주의사항: 가상소멸자 vs 순수가상소멸자
    // virtual ~IPerson() = default;    // 가상소멸자 활성시 기본으로 생성한 소멸자를 쓰겠다는 뜻. 오버라이드 강제는 없음

    // 위 코드 까지만 쓴다면, 인터페이스클래스(순수가상함수로만 이루어진 클래스)의 소스파일(.cpp)를 작성하지 않아도 됨.


    virtual ~IPerson() = 0;         //! 하지만 예외적으로 순수가상소멸자 사용시 Interface도 소스파일을 제공해야함!
};
