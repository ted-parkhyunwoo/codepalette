#include <iostream>
#include <vector>
#include <thread>

// emplace_back(객체):암묵적 과 push_back(std::move(객체)):명시적  은 이동생성자 호출이 일어남을 서술한다.

void task() {
    std::cout << "start!\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));   // 그냥 5초간  대기하는 함수
    std::cout << "finish.\n";
}

int main() {

    // std::thread(task) 를 직접 실행하는 램다라면 emplace_back(makeThread) 로 사용하지만, rvalue리턴의 객체 소유권 이전(이동) 을 서술하기 위해 객체를 직접 리턴한다.
    auto makeThread = [] () {
        return std::thread(task);       // rvalue로 리턴. 이동생성자 호출됨
    };

    std::vector<std::thread> threads;

    //! epmpalce_back() 은 이동 발생.. push_back() 도 std::move()를 직접 사용하면 이동 발생. 
    //! 따라서 join()의 for문은 타입에 참조자 &를 사용한다.(thread는 복사금지)
    for (int i = 0; i < 5; i++) {
        threads.push_back(std::move(makeThread()));             // 명시적 move는 push_back도 사용 가능. 조건: 램다 등에서 객체를 rvalue로 리턴시.
        threads.emplace_back(makeThread());                     // emplace_back() 은 00_thread.cpp 참고.
    }

    for (auto& t : threads) {                                   //! 아주 중요한 조건으로 타입에 &를 붙여 참조하여야 함.(thread는 복사금지)
        t.join();
    }

    return 0;
}