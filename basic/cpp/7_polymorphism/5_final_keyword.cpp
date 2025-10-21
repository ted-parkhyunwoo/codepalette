#include <iostream>

// final 지정자. 클래스, 가상함수(멤버함수)에 사용가능. 이후 상속불가처리함

/*

class A {
public:
    virtual void do_something();
};

class B : public A {
public:
    virtual void do_something() override final;
    // 함수에서의 final 지정자(키워드) 는 이후 멤버함수의 오버라이드 불가처리 함.
    // 따라서 클래스 C에선 오류발생. (상속을 A로 바꾸면 여전히 사용 가능.)
};

class C : public B {
public:
    virtual void do_something();    
};

class a {
public:
    virtual void do_something();
};

class b final: public a {   
// 클래스에서의 final은 이후 클래스 상속을 불가처리.
public:
    virtual void do_something();
};

class c: public b {
public:
    virtual void do_something();
};

*/