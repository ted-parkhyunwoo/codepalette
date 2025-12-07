#include <iostream>
#include <variant>

//! variant 타입을 쓰면 다타입 (2개 이상도 가능) 설정 가능.
// 선언은 std::variant<int, double> VarName 등과 같이 한다.
// 타입 확인은 std::holds_alternative<TYPE>(VarName) 으로 하며 bool 타입으로 리턴된다.
// 사용은 std::get<TYPE>(VarName) 으로 사용한다

struct Node {
    int value;
    Node* next;
};

struct Entry {
    std::string name;
    std::variant<Node*, int> v;
};

void f(Entry* pe) {
    if (std::holds_alternative<int>(pe->v)) {
        std::cout << "Integer: " << std::get<int>(pe->v) << '\n';
    } else if (std::holds_alternative<Node*>(pe->v)) {
        Node* node = std::get<Node*>(pe->v);
        if (node) {
            std::cout << "Pointer to Node with value: " << node->value << '\n';
        } else {
            std::cout << "Null pointer\n";
        }
    }
}

int main() {
    Node node = {42, nullptr}; // Node 초기화
    Entry e1 = {"Example1", 100}; // 정수 타입 Entry
    Entry e2 = {"Example2", &node}; // 포인터 타입 Entry

    f(&e1); // 정수 타입 출력
    f(&e2); // 포인터 타입 출력

    return 0;
}