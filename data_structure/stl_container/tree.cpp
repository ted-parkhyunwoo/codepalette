#include <iostream>

struct node {
    int val;
    node* left;
    node* right;

    node(int value) : val(value), left(nullptr), right(nullptr) {}
};

class tree {
    private:
        node* root; // 트리의 루트 노드
    public:
        tree(int rootValue) {
            root = new node(rootValue);
        }

        ~tree() {
            deleteTree(root);
        }

        void addLeft(node* parent, int value) {
            if (parent->left == nullptr) {
                parent->left = new node(value);
            } else {
                std::cerr << "Left child already exists!" << std::endl;
            }
        }

        void addRight(node* parent, int value) {
            if (parent->right == nullptr) {
                parent->right = new node(value);
            } else {
                std::cerr << "Right child already exists!" << std::endl;
            }
        }

        node* getRoot() {
            return root;
        }

        void printTree(node* current) {
            if (current == nullptr) return;
            std::cout << current->val << " ";
            printTree(current->left);
            printTree(current->right);
        }

    private:
        void deleteTree(node* current) {
            if (current == nullptr) return;
            deleteTree(current->left);
            deleteTree(current->right);
            delete current;
        }
};

int main() {
    tree t(5); // 루트 노드 값 5
    node* root = t.getRoot();

    t.addLeft(root, 2);  // 루트의 왼쪽 자식 추가
    t.addRight(root, 3); // 루트의 오른쪽 자식 추가

    t.addLeft(root->left, 1);  // 왼쪽 자식의 왼쪽 자식 추가
    t.addRight(root->left, 4); // 왼쪽 자식의 오른쪽 자식 추가

    t.printTree(root); // 트리 출력 (전위 순회)
    return 0;
}

