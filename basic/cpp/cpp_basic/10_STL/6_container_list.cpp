#include <iostream>
#include <list>
#include <algorithm>


/* 
list = 연결리스트 (양방향.)  -참고 단방향은 forward_list. (back관련이 사용 안됨. front만 가능.)

설명:

    각 요소들이 heap에 연속된 공간에 들어가지 않고 여기저기 흩어져있음.
    다만 이전요소, 다음요소의 포인터가 같이 들어감.
      
    [1]  <->  [2]  <->   [3] 
    <-> 는 사실상 -> 와 <- 두가지이며, 서로 이전이 뭔지, 다음이 뭔지만 알수있음

메모리 구조:

    list 자체 = 
        front 포인터(head), end 포인터(tail), list의 크기(노드의 갯수) 순서로 메모리에 저장됨.
    front(첫번 째 노드) =
        tail 포인터(다음노드), head 포인터(처음이므로 list자체 포인터), 데이터 순으로 저장됨.


장점:
    노드의 포인터만 수정하면 되므로, 크기 조절과 데이터 삽입 삭제가 굉장히 빠름 (노드만 수정하면 됨)
    특히 처음과 끝의 삽입 삭제가 편함.
    즉 데이터의 변경사항이 vector등에 비해 빠름 (삽입과 삭제 시 array나 vector는 뒤로 한칸 밀거나 당겨야함. 연결리스트는 데이터의 직접 이동 없이 포인터만 즉시 수정)
    
    양방향 순회 한정 begin, rbegin의 사용과 ++it, --it 이동이 빠름.

단점:
    데이터를 찾을 때 나올 때 까지 처음부터 탐색해야됨(순차접근)
    연속된 메모리 공간이 아니기 때문에 index로 접근불가.


활용:
    인덱스 접근을 빼고는 모든 것은 거의 그대로 사용 가능함.
    find, empty, insert, erase, 
    push_back, emplace_back, pop_back

    push_front, emplace_front, pop_front (list는 가능)
    resize(노드갯수) = 사이즈를 변경. 줄이면 초과노드 삭제, 늘리면 0으로 채움.

*/

void printList(std::list<int> user_list) {
    for (auto it = user_list.begin(); it != user_list.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}


int main() {
    std::list<int> myList = {1,2,4};
    printList(myList);

    auto it = std::find(myList.begin(), myList.end(), 4);

    myList.insert(it, 3);
    printList(myList);
    myList.erase(it);   // it은 여전히 정의한대로 4의 위치를 포인팅 하므로 4를 삭제.
    printList(myList);

    myList.push_back(4);
    myList.push_front(0);
    printList(myList);


    return 0;
}