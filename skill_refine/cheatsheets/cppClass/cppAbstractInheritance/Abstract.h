
// 추상클래스: 부모클래스이지만, 일부 행동은 상속(정확히는 구체클래스) 에서 구현하도록 강제유도.
class Abstract {
    protected:
        int userId;

    public:
        Abstract(int id) : userId{id} {}
        int getId() { return this->userId; }

        // sayHello() 의 행동은 직접 구현하도록 유도하는 순수가상함수 (추상클래스에 순수가상함수가 포함되면 추상클래스 타입/인스턴스의 객체를 만들 수 없다)
        virtual void sayHello() = 0;

        // 가상함수지만 행동을 구현할 수는 있음.
        virtual void sayHi() {
            std::cout << "HI\n";
        }

};