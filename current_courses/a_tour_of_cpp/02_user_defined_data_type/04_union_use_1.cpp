#include <iostream>
#include <string>

//! union을 쓰지 않는 경우: Entry 에서 두가지 데이터 타입을 사용하므로, 메모리 공간이 낭비된다. 

enum class Type { ptr, num }; // 데이터 타입을 구분하기 위한 열거형

struct Node {
    int value;
    Node* next;
};

struct Entry {
    std::string name; // 이름
    Type t;           // 데이터 타입
    Node* p;          // 포인터 타입일 경우 사용
    int i;            // 정수 타입일 경우 사용
};

void f(Entry* pe) {
    if (pe->t == Type::num) {
        std::cout << "Integer: " << pe->i << '\n';
    } else if (pe->t == Type::ptr) {
        if (pe->p) {
            std::cout << "Pointer to Node with value: " << pe->p->value << '\n';
        } else {
            std::cout << "Null pointer\n";
        }
    }
}

int main() {
    Node node = {42, nullptr}; // Node 초기화
    Entry e1 = {"Example1", Type::num, nullptr, 100}; // 정수 타입 Entry
    Entry e2 = {"Example2", Type::ptr, &node, 0};     // 포인터 타입 Entry

    f(&e1); // 정수 타입 출력
    f(&e2); // 포인터 타입 출력

    return 0;
}