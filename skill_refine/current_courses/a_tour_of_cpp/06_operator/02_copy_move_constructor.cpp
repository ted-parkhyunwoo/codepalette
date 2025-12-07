#include <iostream>
#include <cassert>

class Vector {
private:
    int sz;
    int* data;

public:
    // 기본 생성자
    Vector(int size = 0) : sz(size), data(size ? new int[size]() : nullptr) {}

    // 소멸자
    ~Vector() {
        delete[] data;
    }

    // 복사 생성자
    Vector(const Vector& other) : sz(other.sz), data(new int[other.sz]) {
        for (int i = 0; i < sz; ++i)
            data[i] = other.data[i];
    }

    // 복사 대입 연산자
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;

        delete[] data;
        sz = other.sz;
        data = new int[sz];
        for (int i = 0; i < sz; ++i)
            data[i] = other.data[i];
        return *this;
    }

    // 이동 생성자
    Vector(Vector&& other) noexcept : sz(other.sz), data(other.data) {
        other.sz = 0;
        other.data = nullptr;
    }

    // 이동 대입 연산자 (이동할당)
    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;

        delete[] data;
        sz = other.sz;
        data = other.data;

        other.sz = 0;
        other.data = nullptr;
        return *this;
    }

    // operator+ 오버로딩 (두 벡터 합산)
    friend Vector operator+(const Vector& a, const Vector& b) {
        assert(a.sz == b.sz && "Vector sizes must match!");
        Vector res(a.sz); // 임시 객체 생성
        for (int i = 0; i < a.sz; ++i)
            res.data[i] = a.data[i] + b.data[i];
        return res; // 임시 객체 반환
    }

    // operator[] 오버로딩
    int& operator[](int i) {
        assert(i >= 0 && i < sz);
        return data[i];
    }

    const int& operator[](int i) const {
        assert(i >= 0 && i < sz);
        return data[i];
    }

    // 크기 반환
    int size() const { return sz; }
};

int main() {
    Vector v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    Vector v2(3);
    v2[0] = 4; v2[1] = 5; v2[2] = 6;


    // 이동생성자, 이동할당연산은 필요에따라 자동호출됨. 주로 임시객체, 소유권이전 발생시 사용됨.

    //! 이동생성자는 임시객체 생성시 컴파일러가 알아서 호출하도록 만듬. operator+ 부분에서도 임시객체 생성이라는데, 어떻게 작동하는지 아직 알 수가 없음. <- 아래에 내용추가.

    //! 추가: std::move(객체)로 대입하는등 명시적으로 하지 않으면 컴파일러가 암묵적으로 호출하긴 하는데, 보통은 이동할당/이동생성자 호출이 잘 일어나지 않음. 함수의 return값으로 받거나, 임시객체를 다룰 때에 일어남.
    //! 핵심은 이동이 복사비용을 아끼기도 하지만, 이동시 객체 내 포인터를 소유권을 넘기면서 nullptr로 지정함으로 안전한 메모리 해제가 핵심임.
    Vector v3 = v1 + v2;  // 이동 생성자 활용될 수 있음 operator+ 함수에서 리턴값rvalue으로 임시객체를 뱉기 때문에.

    Vector v4(3);
    v4 = std::move(v3);  // 이동 대입 연산자 호출

    for (int i = 0; i < v4.size(); ++i)
        std::cout << v4[i] << " ";  // 5 7 9

    std::cout << std::endl;
    return 0;
}
