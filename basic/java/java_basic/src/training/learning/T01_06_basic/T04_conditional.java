package training.learning.T01_06_basic;

public class T04_conditional {
    public static void main(String[] args) {
        // if - else
        char signal = 'G';
        if (signal == 'G') {
            System.out.println("Green. 통과하세요");
        } else if (signal == 'Y') {
            System.out.println("Yellow. 주의하세요");
        } else if (signal == 'R') {
            System.out.println("RED! 정지.");
        } else {
            System.out.println("없는 신호 입니다");
        }

        // switch문: 다른언어와 비슷하게 break에 주의할 것.
        // java 에선 String 도 사용가능(java7부터)
        String User = "Ted";
        switch (User) {
            case "Ted":
                System.out.println("Hello Admin.");
                break;
            case "Hyeree":
                System.out.println("Hello Ted's wife.");
                break;
            // 조건 묶기:Full Through
            case "babo":
            case "멍청이":
                System.out.println("바보들은 나가주세요.");
                break;
            default:
                System.out.println("Hello " + User + '.');
        }
    }
}
