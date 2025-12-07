package training.learning.T01_06_basic;

public class T05_loop {
    public static void main(String[] args) {
        int i;
        for (i=5; i< 10; i++){
            System.out.println(i);
        }
        while (i > 5) {
            --i;
        }

        // continue; 코드를 실행하지 않고 다음 루프 진행
        // break; 루프 종료
    }

}
