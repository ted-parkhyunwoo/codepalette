package fourth;

public class Cond {
    public static void main(String[] args) {
        int age = 8;
        String type = "";
        if (age < 8) {
            type = "아동";
        } else if (age < 20) {
            type = "청소년";
        } else {
            type = "성인";
        }
        System.out.println(type);


        int rank = 1;

        String medalColor;
        switch (rank) {
            case 1: 
                medalColor = "Gold";
                break;
            case 2: 
                medalColor = "Silver";
                break;
            case 3: 
                medalColor = "Bronze";
                break;
            default: 
                medalColor = "Fail";
        }

        // java도 옛날엔 String안됐으나 이제 가능
        switch (medalColor) {
            case "Gold": 
                System.out.println("금메달");
                break;
            case "Silver": 
                System.out.println("은메달");
                break;
            case "Bronze": 
                System.out.println("동메달");
                break;
            default: 
                System.out.println("노메달");
        }

        // 최근엔 람다식으로 작동. break작성X
        switch (medalColor) {
            case "Gold" -> System.out.println("금메달");
            case "Silver" -> System.out.println("은메달");
            case "Bronze" -> System.out.println("동메달");
            default -> System.out.println("노메달");
        }        

    }
}
