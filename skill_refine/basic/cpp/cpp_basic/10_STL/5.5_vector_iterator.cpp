#include <iostream>
#include <algorithm>
#include <vector>


// 다음 코드와 같이 vector는 삽입/삭제/수정 등으로 iterator가 손상될 수 있음(무효)
// 손상된 it은 vector 가 새로운 공간에 재할당 되더라도 it은 재할당 vector의 어딘가를 무작위로 가리킬 수 있음

void printVector(std::vector<int>& user_vec) {

    for (const int& num:user_vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {

    std::vector<int> myVec{1,2,3,4,5};

    // 3을 타겟으로 하고 여러번 삽입, 삭제등을 하면 위치가 보장되지 않음.
    // 따라서 수정 후에는 필요시 다시 초기화 해야 함.
    auto it = find(myVec.begin(),myVec.end(), 3);
    printVector(myVec);

    myVec.erase(it);
    printVector(myVec);

    myVec.insert(it, 3);
    printVector(myVec);

    for (int i = 0; i < 10; i++){
        myVec.push_back(9);
    }
    // for (int i = 0; i < 10; i++){
    //     myVec.pop_back();
    // }



    myVec.erase(it);
    printVector(myVec);

    myVec.push_back(3);
    myVec.push_back(123);
    printVector(myVec);
    myVec.erase(it);
    printVector(myVec);



    return 0;
}