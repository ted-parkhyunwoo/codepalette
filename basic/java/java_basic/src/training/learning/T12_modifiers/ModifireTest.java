package training.learning.T12_modifiers;

public class ModifireTest {
    public static void main(String[] args) {
        // 접근제한자 테스트.
        ModifireClass t = new ModifireClass();
        System.out.println(t.test);
        System.out.println(t.test2);
        System.out.println(t.test4);
        ModifireClass2 t2 = new ModifireClass2();
        System.out.println(t2.test);
        // 자식클래스의 test2는 부모클래스와 마찬가지로 protected다.
        System.out.println(t2.test2);
        System.out.println(t2.test4);

        // 자식클래스의 test3는 private에서 public으로 전환되었다.
        System.out.println(t2.test3);

        t.printHey();
        t2.printHey();

        // t객체의 test3는 private이므로, 정보은닉되어 메서드로만 접근된다.
        t.printTest();
    }
}
