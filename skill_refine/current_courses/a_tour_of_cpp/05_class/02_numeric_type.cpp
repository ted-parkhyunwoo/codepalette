#include <iostream>


class complex {
    double re, im;
public:
    // constructor
    complex(double r, double i) : re{r}, im{i} {}
    complex(double r) : re{r}, im(0.0) {}
    complex(): re(0), im(0){}

    // methods : 함수오버로딩으로 매개변수에 인수입력이 없으면 값리턴, 있으면 대체로 작동.
    // 실수, 허수 get
    double real() const { return re; }
    double imag() const {return im;}
    // 실수, 허수 대입
    void real(double d) { re = d;}
    void imag(double d) { im = d;}

    // 복합대입연산자(복합할당연산자) +=, -=, *=, /=오버로딩
    complex& operator+=(complex z) {
        re += z.re;
        im += z.im;
        return *this;
    }
    complex& operator-=(complex z) {
        re -= z.re;
        im -= z.im;
        return *this;
    }

    // 곱셈과 나눗셈은 좀 다름. (복소수의 특징인듯.)
    complex& operator*=(complex z) {
        double r = re * z.re - im * z.im;
        double i = re * z.im + im * z.re;
        re = r;
        im = i;
        return *this;
    }
    complex& operator/=(complex z) {
        double denom = z.re * z.re + z.im * z.im;
        double r = (re * z.re + im * z.im) / denom;
        double i = (im * z.re - re * z.im) / denom;
        re = r;
        im = i;
        return *this;
    }

    // 산술 연산자 오버로딩 (비멤버 함수로 선언. 클래스 밖에 선언할 경우 friend 안써도됨.)
    // complex b는 const & 로 하기 권장되나, 크기가 일단 크지 않아서 냅둠.
    friend complex operator+(complex a, complex b) { return a += b; }

};
// 산술연산자 (이항, 단항) 오버로딩
complex operator-(complex a, complex b) { return a -= b; }
complex operator-(complex a) { return {-a.real(), -a.imag()}; }     // 단항 -. 즉 * -1처리.
complex operator*(complex a, complex b) { return a *= b; }
complex operator/(complex a, complex b) { return a /= b; }



int main() {
    complex a;
    a.real(3);
    a.imag(5);
    complex b{1, 1};
    a = a + b;
    a = -a;
    
    std::cout << a.real() << " " << a.imag() << std::endl;
    return 0;
}