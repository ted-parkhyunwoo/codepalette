#include <iostream>

// 이진트리 예제


// node구조체
struct node {
    std::string name;
    node*       left;
    node*       right;
};

// tree 구조체(public 클래스)
struct tree {
    node*       root;

    static tree init_tree(const std::string& name) {
        tree        t;
        t.root =    new node{ name, NULL, NULL };
        return      t;
    }

    static node* find(node* root, const std::string& name) {
        // 재귀식으로 name에 해당하는 노드 찾기. 
        if (root == NULL)           return NULL;
        if (root->name == name)     return root;        
        node* leftFound =            tree::find(root->left, name);
        if (leftFound != NULL)      return leftFound;
        return                      tree::find(root->right, name);
    }

    bool addSub(const std::string& p, const std::string& c) {
        // 특정노드(p)의 name의 자식으로 c를 추가
        node* pNode =    find(root, p);

        if (!pNode) {
            // p의 노드를 찾지못함
            printf("[FAIL]'%s'의 노드를 찾지 못함\n", p.c_str());
            return false;
        }

        if (pNode->left && pNode->right) {
            // p의 노드에 이미 두개가 차있음.
            printf("[FAIL]'%s'의 노드는 이미 2개의 하위노드를 갖고있음\n", p.c_str());
            return false;
        }

        //찾은경우
        if (!pNode->left)       pNode->left =   new node {c, NULL, NULL};
        else                    pNode->right =  new node {c, NULL, NULL};
        printf("[OK]'%s'에 '%s'추가성공\n", p.c_str(), c.c_str());
        return true;
    }
};


int main() {

    tree my_tree = tree::init_tree("하하");
    my_tree.addSub("없는것", "추가해");                 // [FAIL]'없는것'의 노드를 찾지 못함
    my_tree.addSub("하하", "히히");                     // [OK]'하하'에 '히히'추가성공
    my_tree.addSub("하하", "헤헤");                     // [OK]'하하'에 '헤헤'추가성공
    my_tree.addSub("하하", "이미두개추가됐을걸");       // [FAIL]'하하'의 노드는 이미 2개의 하위노드를 갖고있음
    my_tree.addSub("히히", "헤헤헤헤");                 // [OK]'히히'에 '헤헤헤헤'추가성공
    my_tree.addSub("헤헤헤헤", "헣헣헣헣헣헣");         // [OK]'헤헤헤헤'에 '헣헣헣헣헣헣'추가성공
    my_tree.addSub("히히", "후후후후");                 // [OK]'히히'에 '후후후후'추가성공
    my_tree.addSub("헣헣헣헣헣헣", "흫흫흫흫흫흫흫흫"); // [OK]'헣헣헣헣헣헣'에 '흫흫흫흫흫흫흫흫'추가성공


/*  구조체계
                      하하(root)
                     /    \
            L: 히히        R: 헤헤
            /     \
   L: 헤헤헤헤    R: 후후후후
         /
L: 헣헣헣헣헣헣
      /
L: 흫흫흫흫흫흫흫흫

*/

    return 0;
}