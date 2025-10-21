package java_class.my_module;

public class Person {
    private String name;
    private int age;

    public Person() { 
        this("null", 0);
    }
    public Person(String name, int age) {
        setInfo(name, age);
    }

    protected String getName() { return this.name; }
    protected int getAge() { return this.age; }

    public void setName(String name) { this.name = name; }
    public void setAge(int age) { this.age = age; }
    public void setInfo(String name, int age) {
        this.name = name;
        this.age = age;
    }

    // 자바 맹점. 만약 현 클래스가 abstract라면 기본구현 한 상태에서 반드시 오버라이드를 강제 할 수 없음. 따라서 interface를 사용하고, 기본구현 클래스를 사용하는게 나을듯.
    @Override
    public String toString() {
        return ("name: " + this.name + ", age: " + this.age);
    }
}