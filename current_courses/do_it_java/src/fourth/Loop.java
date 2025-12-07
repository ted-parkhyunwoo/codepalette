package fourth;

public class Loop {
    public static void main(String[] args) {
        int a = 0;

        // while-loop
        while (true) {
            if (a >= 10) break;     // while조건문에 삽입가능
            if (a == 3) {
                a++;
                continue;           // 특정조건은 건너뜀
            }
            System.out.print(a);
            a++;
        }
        System.out.println();


        a = 0;
        while (a < 10) 
            System.out.print(a++);
        System.out.println();

        // 조건식에 맞지 않는데도 1회 실행됨
        a = 11;
        do System.out.print(a++);
        while (a < 1);
        System.out.println();


        // for loop: 선언 조건 증감
        for (a = 0; a < 10; ++a) 
            System.out.print(a);
        System.out.println();


        // 99단
        for (int i = 2; i < 10; ++i) {
            for (int j = 1; j < 9; ++j) 
                System.out.printf("%d x %d = %d\n", i, j, i*j);
            System.out.println();
        }

        // +@ stars
        for (int i = 1; i < 6; ++i) {
            for (int j = 1; j <= i; ++j) 
                System.out.print("*");
            System.out.println();
        }

        // +@ pyramid2
        int stairs = 5;
        for (int i = 0; i < stairs; ++i) {
            int stars = i * 2 + 1;
            int spaces = (((stairs - 1) * 2 + 1) - stars) / 2;
            for (int sp = 0; sp < spaces; ++sp) 
                System.out.print(" ");
            for (int st = 0; st < stars; ++st) 
                System.out.print("*");
            
            System.out.println();
        }

        // switch-case yield. 리턴(yield) 값으로 res를 할당할 경우(람다식의 일종)
        String res = switch(10) {
            case 5:  yield "five";
            case 10: yield "ten";
            default: yield "fail";
        };

        String res2 = switch(10) {
            case 5 -> "five";
            case 10 -> "ten";
            default -> "fail";
        };

        System.out.println(res);
        System.out.println(res2);

    }
}
