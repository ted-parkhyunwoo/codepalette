package training.learning.T12_modifiers;

// cpp 처럼 접근제한자를 묶을 순 없음. 정보은닉과 캡슐화의 문법과 철학은 cpp와 java가 비슷함.

public class EncapsulationTest {
    // 정보은닉: 데이터의 접근제한 처리.
    private int score;
    private String name = null;

    // 캡슐화: 은닉된 데이터의 getter setter 생성.(메서드로만 접촉가능)
    public int getScore() { return this.score; }
    public void setScore(int score) { if (score >= 0 && score <= 100) this.score = score; }

    public String getName() { return this.name; }
    public void setName(String name) { if (name != null)  this.name = name; }

    @Override
    public String toString() { return "name: " + getName() + ", score: " + getScore(); }

    // 실행예제
    public static void main(String[] args) {
        EncapsulationTest e = new EncapsulationTest();
        e.setName("TED PARK");
        e.setScore(30);
        System.out.println(e.getScore());
        // e.toString() 함수는 e로 단축된다. - 내부적으로 e.toString()호출
        System.out.println(e);


        // +@. toString()에 관해.(큰의미없음)
        // 아래와같이 쓸때는 toString()을 호출해야한다.
        String res = e.toString();
        //  이상하게 이때는 가능하다.
        String res2 = e + " 입니다.";
        // 형변환을 이용해도 불가.
//        String res3 = (String) e;
        String res4 = "" + e;   // 큰 의미없는 편법.
        System.out.println(res + res2 + res4);
    }

}
