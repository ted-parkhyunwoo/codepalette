package java_class;
import java_class.my_module.Person;
import java_class.my_module.PersonWithPhone;

public class Main {
    public static void main(String[] args) {
        Person a = new Person();
        a.setName("kim");
        a.setAge(32);
        System.out.println(a);

        Person noNameClassTest = new Person() {
            @Override
            public String toString() {
                return "noName Class: 익명클래스 Overrided toString() method always return this string.";
            }
        };

        System.out.println(noNameClassTest);


        PersonWithPhone b = new PersonWithPhone();
        b.setInfo("ted", 32, "010-1234-5678");
        System.out.println(b);

        PersonWithPhone c = new PersonWithPhone();
        c.setInfo("ted", 32, "010-1234-5678");
        
        System.out.println(b.equals(c));


    }
}