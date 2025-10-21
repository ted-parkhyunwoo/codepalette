#include <iostream>

class Base { 

protected:
public:
    virtual void Say() const {
        std::cout << "This is a Base object." << std::endl;
    }
    virtual ~Base() {}
};


class Derived : public Base{
public:

    //! override 키워드(지정자) 를 지정해줌으로써 상속관계(:public Base) 를 까먹었거나, const를 까먹었을 경우 오류 표시됨.
    // 실질적인 기능은 가독성 향상과 에러 사전 방지 효과 정도임.
    virtual void Say() const override {
        std::cout << "This is a Derived object." << std::endl;
    }

};

int main() {
    const Base* obj = new Derived();
    obj->Say();

    delete obj;

    return 0;
}