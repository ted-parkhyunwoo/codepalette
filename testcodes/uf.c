#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// find
int find(int* node, int sz, int x) {
    if (node[x] != x) 
        node[x] = find(node, sz, node[x]);
    return node[x];
}

// union
void unite(int* node, int sz, int a, int b) {
    int rootA = find(node, sz, a);
    int rootB = find(node, sz, b);
    if (rootA != rootB) 
        node[rootB] = rootA;
}

// connected
int connected(int* node, int sz, int a, int b){
    return find(node, sz, a) == find(node, sz, b);
}

// make node
int* makeNode(int sz) {
    int* arr = malloc(sizeof(int) * sz);
    for (int i = 0; i < sz; ++i) 
        *(arr + i) = i;
    return arr;
}

// print arr. (array, type, size)
void printArr(void* arr, const char* type, int sz) {
    if (strcmp(type, "int") == 0) {
        int *a = arr;
        for (int i = 0; i < sz; ++i)
            printf("%d ", a[i]);
    } 
    else if (strcmp(type, "double") == 0) {
        double *a = arr;
        for (int i = 0; i < sz; ++i)
            printf("%.2f ", a[i]);
    } 
    else if (strcmp(type, "char") == 0) {
        char *a = arr;
        for (int i = 0; i < sz; ++i)
            printf("%c ", a[i]);
    } 
    else {
        printf("[unsupported type]");
    }
    printf("\n");
}


int main() {
    int arrSz = 10;
    char* arr = malloc(sizeof(char) * arrSz);
    // arr의 데이터: A ~ J 의 문자.
    for (int i = 0; i < arrSz; ++i) {
        *(arr + i) = 'A' + i;
    }
    printArr(arr, "char", arrSz);

    // arr의 node 생성.
    int* arrNode = makeNode(arrSz);
    printArr(arrNode, "int", arrSz);

    // node 연결
    unite(arrNode, arrSz, 0, 3);
    unite(arrNode, arrSz, 3, 2);

    // boolean 결과.
    int test1 = connected(arrNode, arrSz, 0, 3);
    int test2 = connected(arrNode, arrSz, 0, 1);
    printf("%d, %d\n", test1, test2);

    // node 직접 print 해보기.
    printArr(arrNode, "int", arrSz);

    free(arr);
    free(arrNode);
    return 0;
}