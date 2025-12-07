#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
// #include <functional>

void task(const std::string& name, int duration) {
    std::cout << name << " 시작!\n";
    std::this_thread::sleep_for(std::chrono::seconds(duration)); // 일정 시간 동안 대기
    std::cout << name << " 완료!\n";
}


//! cpp의 멀티스레드 사용 (표준라이브러리 thread.) 
int main() {

    //! 1. 초기화 형태는 매개변수로 (콜백, 콜백의 매개변수들) 로 표현된다. 객체생성과 동시에 호출됨.
    std::thread t1(task, "Task 1", 5); // 5초 동안 대기
    std::thread t2(task, "Task 2", 5); // 5초 동안 대기

    //! 2. 스레드가 종료되면 join()으로 자원을 회수시킨다.
    t1.join(); // Task 1 종료 대기
    t2.join(); // Task 2 종료 대기

    std::cout << "모든 작업 완료!" << std::endl;


    //! 3. 만약 원하는 시점에 쓰레드를 실행하려면 램다로 미리 정의. 
    // std::function<void()> delayedTask = []() { task("Task 1", 5); };     //(functional 필요)
    auto delayedTask2 = [](int num, int during) { 
        std::ostringstream oss;
        oss << "Task " << num;
        task(oss.str(), during); 
    };        // auto 로 하면 functional필요 없음
    std::thread t(delayedTask2, 205, 10);       // task number:205, 10초동안.
    t.join();

    //! 4. for문으로 동시실행해보기: 여러 인스턴스를 vector에 넣는건 일반적인 push_back은 안됨.
    std::vector<std::thread> threads;
    for (int i = 1; i <= 10; i++) {
        // push_back = 이미 생성된 객체를 복사 / 이동할땐 가능.
        threads.emplace_back(delayedTask2, i, 10);  
        // vector에 먼저 넣고, 내부에서 생성됨. (string등 처럼 객체가 비용이 비싸면 이쪽이 효율이 좋음.)
    }

    // 모두 조인: 만약 직접 join()하기 싫다면, 사용자정의 쓰레드 00_thread_class.cpp 참고
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}