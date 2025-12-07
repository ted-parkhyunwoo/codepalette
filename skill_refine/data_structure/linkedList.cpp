#include <iostream>
#include <stdexcept>

template <typename T>
struct node {
    node* front; // 이전 노드
    T val;       // 값
    node* back;  // 다음 노드
};

template <typename T>
class LinkedList {
private:
    node<T>* root; // 첫 번째 노드
    node<T>* last; // 마지막 노드
    int sz;        // 리스트 크기

public:
    // 생성자: 초기값으로 리스트 생성
    LinkedList(T num) {
        root = new node<T>;
        root->val = num;
        root->front = nullptr;
        root->back = nullptr;
        last = root;
        sz = 1;
    }

    // push_back: 리스트 끝에 새 노드 추가
    void push_back(T val) {
        node<T>* newNode = new node<T>;
        newNode->val = val;
        newNode->front = last;
        newNode->back = nullptr;

        last->back = newNode;
        last = newNode;
        sz++;
    }

    // push_front: 리스트 앞에 새 노드 추가
    void push_front(T val) {
        node<T>* newNode = new node<T>;
        newNode->val = val;
        newNode->front = nullptr;
        newNode->back = root;

        if (root != nullptr) {
            root->front = newNode;
        } else {
            last = newNode;
        }

        root = newNode;
        sz++;
    }

    // back: 마지막 노드의 값 반환
    T back() {
        if (last == nullptr) {
            throw std::runtime_error("List is empty. Cannot access back element.");
        }
        return last->val;
    }

    // front: 첫 번째 노드의 값 반환
    T front() {
        if (root == nullptr) {
            throw std::runtime_error("List is empty. Cannot access front element.");
        }
        return root->val;
    }

    // pop_back: 리스트 끝에서 노드 제거
    void pop_back() {
        if (last == nullptr) {
            throw std::runtime_error("List is empty. Cannot pop back element.");
        }

        if (last == root) {
            delete last;
            root = last = nullptr;
        } else {
            node<T>* tmp = last;
            last = last->front;
            last->back = nullptr;
            delete tmp;
        }
        sz--;
    }

    // pop_front: 리스트 앞에서 노드 제거
    void pop_front() {
        if (root == nullptr) {
            throw std::runtime_error("List is empty. Cannot pop front element.");
        }

        node<T>* tmp = root;
        if (root == last) { // 리스트에 노드가 하나만 있는 경우
            root = last = nullptr;
        } else {
            root = root->back;
            root->front = nullptr;
        }
        delete tmp;
        sz--;
    }

    // insert: 주어진 인덱스 위치에 새 노드 삽입
    void insert(int idx, T val) {
        if (idx < 0 || idx > sz) {
            throw std::out_of_range("Index out of range");
        }

        if (idx == 0) { // 맨 앞에 삽입
            push_front(val);
            return;
        }

        if (idx == sz) { // 맨 뒤에 삽입
            push_back(val);
            return;
        }

        node<T>* current = root;
        for (int i = 0; i < idx; ++i) {
            current = current->back;
        }

        node<T>* newNode = new node<T>;
        newNode->val = val;
        newNode->back = current;
        newNode->front = current->front;

        if (current->front) {
            current->front->back = newNode;
        }
        current->front = newNode;

        sz++;
    }

    // erase: 주어진 인덱스 위치의 노드 삭제
    void erase(int idx) {
        if (idx < 0 || idx >= sz) {
            throw std::out_of_range("Index out of range");
        }

        if (idx == 0) { // 맨 앞 노드 삭제
            pop_front();
            return;
        }

        if (idx == sz - 1) { // 맨 뒤 노드 삭제
            pop_back();
            return;
        }

        node<T>* current = root;
        for (int i = 0; i < idx; ++i) {
            current = current->back;
        }

        current->front->back = current->back;
        current->back->front = current->front;

        delete current;
        sz--;
    }

    // size: 리스트 크기 반환
    int size() {
        return sz;
    }

    // empty: 리스트가 비어 있는지 확인
    bool empty() {
        return root == nullptr;
    }

    // [] 오버로딩: 특정 인덱스의 값 반환
    T& operator[](int idx) {
        if (idx < 0 || idx >= sz) {
            throw std::out_of_range("Index out of range");
        }
        node<T>* n = root;
        for (int i = 0; i < idx; i++) {
            n = n->back;
        }
        return n->val;
    }

    // printList: 리스트의 모든 요소 출력
    void printList() {
        node<T>* current = root;
        while (current != nullptr) {
            std::cout << current->val << " ";
            current = current->back;
        }
        std::cout << std::endl;
    }

    //! 이터레이터 클래스를 작성하지 않는 이상, 아래의 코드로는 어차피 범위기반for문에선 작동안되는 상태임. 혹시 모르니 서적 참고하여 그대로 구현 다시해볼것. -> it++ 등의 연산이 되질 않아 작동이 안되는것으로 판단됨. 이터레이터클래스를 만들거나 vector로 임시변환하는등의 꼼수가 아니면 일반배열(c스타일) 처럼 쉽게 begin(), end() 함수 작성 불가.
    // // begin: 첫 번째 노드를 반환
    // T* begin() {
    //     return root;
    // }

    // // end: nullptr을 반환 (리스트의 끝을 나타냄)
    // T* end() {
    //     return last;
    // }

    // 소멸자: 동적 메모리 해제
    ~LinkedList() {
        node<T>* current = root;
        while (current != nullptr) {
            node<T>* next = current->back;
            delete current;
            current = next;
        }
    }
};

int main() {
    // TEST CODES
    LinkedList<int> intList(10);
    intList.push_back(20);
    intList.push_back(30);
    intList.push_back(50);
    intList.insert(3, 40);
    intList.erase(4);
    intList.printList();

    // 범위기반 테스트코드(실패. 이터레이터 클래스 작성필요.)
    // for (auto e : intList) {
    //     std::cout << e;
    // }


    // std::cout << "Size: " << intList.size() << std::endl;
    // intList.printList();

    // std::cout << "Last element: " << intList.back() << std::endl;

    // intList.pop_back();
    // std::cout << "After pop_back, size: " << intList.size() << std::endl;
    // intList.printList();

    // intList[0] = 1;
    // intList.printList();

    // for (int i = 0; i < intList.size(); ++i) {
    //     std::cout << intList[i] << ' ';
    // }
    // std::cout << std::endl;

    // LinkedList<double> doubleList(1.1);
    // doubleList.push_back(2.2);
    // doubleList.push_back(3.3);
    // doubleList.printList();

    // LinkedList<std::string> stringList("Hello");
    // stringList.push_back("World");
    // stringList.push_back("!");
    // stringList.printList();

    return 0;
}