#include <iostream>
#include <thread>

class JoinableThread {
public:
    explicit JoinableThread(std::thread t) : t_(std::move(t)) {}

    ~JoinableThread() {
        if (t_.joinable()) {
            t_.join(); // 소멸자에서 자동으로 join 호출
        }
    }

    // 이동 생성자/연산자 필요 (복사는 금지)
    JoinableThread(JoinableThread&& other) noexcept : t_(std::move(other.t_)) {}
    JoinableThread& operator=(JoinableThread&& other) noexcept {
        if (this != &other) {
            if (t_.joinable()) {
                t_.join();
            }
            t_ = std::move(other.t_);
        }
        return *this;
    }

private:
    std::thread t_;
};

void task(const std::string& name) {
    std::cout << name << " 실행 중...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << name << " 완료!\n";
}

int main() {
    JoinableThread t1(std::thread(task, "Task 1"));
    JoinableThread t2(std::thread(task, "Task 2"));

    std::cout << "메인 쓰레드에서 작업 중...\n";

    return 0; // t1과 t2가 스코프를 벗어나며 자동으로 join됨
}