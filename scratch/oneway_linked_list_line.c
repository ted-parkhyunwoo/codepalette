#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 작성하다보니 단방향 선형 연결리스트 됨.
// 추가, 삽입, 삭제 비용이 적으나, 탐색비용이 큼. (addChild만 해도 처음부터 아래까지 탐색. numbering하면 빠르지만 삽입, 중간 삭제시 넘버링 다시해야됨)
// char* name만 동적할당 안하고 현재 리터럴로 사용한다면 문제 없음.
// line node* 에 root 외 last와 size를 넣어보는것을 고려

typedef struct node {
    char* name;
    struct node* child;
    struct node* parent;

} node;

typedef struct line {
    node* root;
} line;

line* initline(char* name) {
    line* newline = malloc(sizeof(line));
    node* root = malloc(sizeof(node));
    root->name = name;
    root->child = NULL;
    root->parent = NULL;
    newline->root = root;
    return newline;
}

//! gpt기준으론 결함 없으나, 로직이 복잡하다함.
node* find(line* rootLine, char* name) {
    node* res = rootLine->root;
    // 자기자신인경우
    if (strcmp(res->name, name) == 0) {
        return res;
    }
    
    while (strcmp(res->name, name) && res->child != NULL) {
        res = res->child;
    }

    // 찾을수 없는경우
    if (strcmp(res->name, name) || (res->child != NULL && strcmp(res->name, name))) {
        return NULL;
    }

    // 찾은경우
    return res;
}

void addChild(line* rootLine, char* name) {
    if (find(rootLine, name) != NULL) {
        printf("추가실패: %s 는 이미 추가된 이름입니다.\n", name);
        return;
    }

    node* lastChild = rootLine->root;
    while (lastChild->child != NULL) {
        lastChild = lastChild->child;
    }

    node* newChild = malloc(sizeof(node));
    newChild->name = name;
    newChild->parent = lastChild;
    newChild->child = NULL;

    lastChild->child = newChild;
    printf("추가성공: %s 를 추가했습니다.\n", name);
}


void delChild(line* rootLine, char* name) {
    // 루트 삭제시 거절하기
    if (find(rootLine, name) == rootLine->root) {
        printf("삭제실패: %s는 최상위 루트입니다\n", name);
        return;
    }

    node* target = find(rootLine, name);
    // 찾을 수 없는경우 처리
    if (target == NULL) {
        printf("삭제실패: %s를 찾을 수 없습니다\n", name);
        return;
    }
    
    node* targetParent = target->parent;
    node* targetChild = target->child;

    targetParent->child = targetChild;

    // 자식이 없는경우 처리
    if (targetChild == NULL) {
        free(target);
        printf("삭제성공: 마지막 자식인 %s를 제거하였습니다\n", name);
        return;
    }

    // 가운데 자식인경우 처리
    targetChild->parent = targetParent;
    free(target);
    printf("삭제성공: %s를 제거하였습니다\n", name);
}

// 구조: 부모를 찾아서 추가. (자식을 찾아서 추가하는 방법도 있을듯. insertParent가 적당할듯 함수명은.)
void insertChild(line* rootLine, char* parentName, char* name) {
    // 부모노드가 있는지부터 탐색
    node* parent = find(rootLine, parentName);

    if (parent == NULL) {
        printf("삽입실패: 부모 %s를 찾을 수 없습니다\n", parentName);
        return;
    }

    // 있다면 진행 (마지막 노드인 경우는 일단 구상중)
    node* originalChild = parent->child;

    node* child = malloc(sizeof(node));
    child->name = name;
    child->child = parent->child;
    child->parent = parent;
    parent->child = child;

    // 부모가 자식이 없던경우를 고려.
    if (originalChild != NULL) {
        originalChild->parent = child;
        printf("삽입성공: %s 와 %s 사이에 %s를 추가\n", parent->name, originalChild->name, child->name);
    }
    
    else 
        printf("삽입성공: %s 의 자식으로 %s를 삽입함(자식이 이미 없는상태)\n", parentName, child->name);
}

void deleteLine(line* rootLine) {
    node* cur = rootLine->root;
    // 위에서부터 내려감. 자식이 NULL이 되기 전까지.
    while (cur != NULL) {
        node* next = cur->child;
        free(cur);
        cur = next;
    }
    free(rootLine);
    printf("메모리 해제 성공\n");
}




int main() {
    line* root = initline("할아버지");
    addChild(root, "아버지"); // 자식 추가해보고 찾기
    addChild(root, "나"); // 자식의 자식을 추가해보기
    addChild(root, "나"); // 있는거 또 추가해보기

    delChild(root, "아들");   // 없는자식 삭제해보기
    delChild(root, "할아버지");     // 루트삭제해보기

    addChild(root, "손자");     // 주석 처리시 변화생김(아래 나, 손자 사이에 삽입하는경우와, 나(자식없음) 뒤에 추가만 하는 경우 두가지가 다르게 작동)
    insertChild(root, "나", "아들");


    addChild(root, "손자");     // 다음 테스트를 위해 마지막노드를 추가함
    delChild(root, "손자");       // 마지막노드 삭제해보기
    delChild(root, "아버지");   // 가운데 자식 삭제해보기

    deleteLine(root);           // 메모리 해제

    return 0;
}



