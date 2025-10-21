package training.testcodes;

public class Pyramid {
    public static void main(String[] args) {
        int height = 6;

        for (int i = 1; i <= height; i++) {
            // 공백 출력
            for (int j = 1; j <= height - i; j++) {
                System.out.print(" ");
            }
            // 별 출력
            for (int k = 1; k <= (2 * i - 1); k++) {
                System.out.print("*");
            }
            // 줄 바꿈
            System.out.println();
        }
    }
}