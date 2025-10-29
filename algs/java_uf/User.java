package java_uf;
import java.util.List;

public class User {
    private String name;
    private int age;
    public User() {}
    public User(String name, int age) { this.name = name; this.age = age; }

    // [ "이름", 나이 ] 형식의 object list.
    public User(List<Object> list) {
        Object n = list.get(0);
        Object a = list.get(1);
        if (n == null || a == null) { return; }
        if (!(n instanceof String) || !(a instanceof Integer)) return;
        String name = (String) n;
        int age = (Integer)a;
        this.name = name;
        this.age = age;
    }

    public String getName() { return this.name; }
    public int getAge() { return this.age; }
    public void setName(String name) { this.name = name; }
    public void setAge(int age) { this.age = age; }
}