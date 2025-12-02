package third;

// operator

public class Main {
    public static void main(String[] args) {

        // 단항: 증감연산
        int a = 1;
        int b = 1;
        System.out.println(++a);    // 2
        System.out.println(b++);    // 1

        // 이항: operand, operator, operand
        int c = a + b;
        System.out.println(c);

        // 삼항연산자: 조건? true: false;
        int d = (a > 1) ? 10 : 20;   // a > 1 == true 이므로 10.
        System.out.println(d);

        // 대입연산자: lValue(변수) <- rValue(값) 우선순위가 가장 낮음
        int e = a + b;

        // 부호연산자: +, -  당연하지만 +는 의미 없음.
        int f = 10;
        System.out.println(-f); // -10
        f = -10;
        System.out.println(+f); // -10. 이런다고 10이 되진 않음.

        // 산술연산자 + - * / %
        // 관계연산자: <, >, >=, <=, ==, !=


        // 논리연산자: &&(논리곱), ||(논리합), !(부정)
        int g = 10;
        int h = 2;
        // 중요: 첫번째 연산이 false이므로, 두번째 조건은 실행되지않고 종료.
        boolean i = ((g = g + 10) < 10) && ((h = h + 2) < 10);
        System.out.println(i);  // false
        System.out.println(g);  // 20
        System.out.println(h);  // 2

        // 마찬가지로, 논리합은 첫번째 항이 true이면, 두번째 항은 실행되지않음
        // 현재 g = 20, h = 2 인 상태에서 아래코드 실행됨.
        i = ((g = g + 10) > 10) || ((h = h + 2) < 10);
        System.out.println(i);  // true
        System.out.println(g);  // 30
        System.out.println(h);  // 2

        // 복합대입연산자: +=, -=, *=, /=, %=

    }
}
