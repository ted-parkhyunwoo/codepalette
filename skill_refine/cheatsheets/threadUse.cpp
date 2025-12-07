#include <iostream>
#include <thread>       // 물리적인 스레드로 태스크를 나누어서 작업
#include <future>       // 논리적인 비동기 프로그래밍용


const size_t THREADS = std::thread::hardware_concurrency();

void sayNum(int num) {
    printf("%d\n", num);
}

int getMulNum(int num) {
    return num * 2; 
}


int main() {
    
    // 스레드 배열(정말 cpu의 물리 쓰레드 사용) : 리턴값을 받는 형태의 함수를 쓰기가 까다로움. 전역화된 배열에 넣어서 꺼내오는 등의 작업으로 할수는 있을듯.
    std::thread* tasks = new std::thread[THREADS];      
    int i = 0;

    // 작업분배
    for (auto it = tasks; it < tasks + THREADS; ++it) 
        *it = std::thread(sayNum, i++);     // 함수와 매개변수를 따로 넣으면 알아서 집어넣어줌

    // 회수(*it은 쓰레드객체이며, 리턴된 값 등이 저장되지 않음.)
    for (auto it = tasks; it < tasks + THREADS; ++it) 
        (*it).join();

    delete[] tasks;



    printf("\n---------\n\n");
    // 논리쓰레드(future, async활용) : .get()등으로 리턴값을 사용할 수 있음.

    std::async(std::launch::async, sayNum, 999).wait();                 // void 형태의 함수를 즉시 실행하려면 .wait()
    std::future<void> as = std::async(std::launch::async, sayNum, 888); // 혹은 이렇게 변수로 저장 후 .wait() 해야 경고가 안뜸
    as.wait();

    int seven = std::async(std::launch::async, getMulNum, 7).get();     // 리턴값이 있다면 이렇게 저장후 사용. (std::cout << 객체.get() 처럼 사용시 오류)
    std::cout << seven << std::endl;



    printf("\n---------\n\n");
    // 반복문을 통한 사용예
    size_t taskSize = 10;
    std::future<int>* asyncTasks = new std::future<int>[taskSize];
    for (int i = 0; i < taskSize; ++i) {
        // 비동기적으로 작업을 던집니다.
        asyncTasks[i] = std::async(std::launch::async, getMulNum, i + 1);
        
    }

    for (int i = 0; i < taskSize; ++i) {
        auto token = asyncTasks[i].get();         // dart 의 await기능처럼 작동.
        std::cout << token << std::endl;
    }
    
    delete[] asyncTasks;

    return 0;
}