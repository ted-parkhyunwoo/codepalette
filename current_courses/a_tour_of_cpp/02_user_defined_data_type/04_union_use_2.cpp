#include <iostream>
#include <string>

struct Node {
    int value;
    Node* next;
};

//! union을 쓸 경우 두가지 타입중 한가지만을 사용할 수 있다. (두 타입중 메모리를 많이 차지하는 타입을 기준으로 메모리 크기가 할당됨.) 하지만 이를위해서 Type를 지정하는건 마찬가지다. Type을 알아야 v.i로 출력할지 v.p 로 출력할지 결정한다.
union Value {
    Node* p; // 포인터 타입
    int i;   // 정수 타입
};

enum class Type { ptr, num }; // 데이터 타입 구분

struct Entry {
    std::string name; // 이름
    Type t;           // 데이터 타입
    Value v;          // 데이터 저장 (포인터 또는 정수)
};

void f(Entry* pe) {
    if (pe->t == Type::num) {
        std::cout << "Integer: " << pe->v.i << '\n';
    } else if (pe->t == Type::ptr) {
        if (pe->v.p) {
            std::cout << "Pointer to Node with value: " << pe->v.p->value << '\n';
        } else {
            std::cout << "Null pointer\n";
        }
    }
}

int main() {
    Node node = {42, nullptr}; // Node 초기화
    Entry e1 = {"Example1", Type::num, {.i = 100}}; // 정수 타입 Entry
    Entry e2 = {"Example2", Type::ptr, {.p = &node}}; // 포인터 타입 Entry

    f(&e1); // 정수 타입 출력
    f(&e2); // 포인터 타입 출력

    return 0;
}