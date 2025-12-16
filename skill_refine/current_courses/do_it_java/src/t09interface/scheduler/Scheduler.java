package t09interface.scheduler;


// 인터페이스 실사용 예제: 상담원과 고객간 상담전화 배분
public interface Scheduler {
    void getNextCall();

    void sendCallToAgent();
}
