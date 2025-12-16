package t09interface.scheduler;

import java.io.IOException;

public class SchedulerTest {
    public static void main(String[] args) throws IOException {
        System.out.println("상담방식 선택:");
        System.out.println("R: 한명씩 차례로 할당");
        System.out.println("L: 쉬고있거나 대기가 가장 적은 상담원 할당");
        System.out.println("P: 우선순위가 높은 고객 먼저 할당");

        int ch = System.in.read();
        Scheduler scheduler = null;

        // 강의는 if문이나, switch문으로 작성해봄
        switch (ch) {
            case 'R':
            case 'r':
                scheduler = new RoundRobin();
                break;
            case 'L':
            case 'l':
                scheduler = new LeastJob();
                break;
            case 'P':
            case 'p':
                scheduler = new PriorityAllocation();
                break;
            default:
                System.out.println("지원하지 않는 기능");
                return;
        }

        scheduler.getNextCall();
        scheduler.sendCallToAgent();


    }
}
