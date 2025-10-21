package training.testcodes.classtest;

// data class: age, name.
public class Class1 {
    private int age;
    private String name;

    // 생성자 오버로딩
    public Class1() {}
    public Class1(int age, String name) {
        this.age = age;
        this.name = name;
    }

    public int getAge() { return this.age; }
    public String getName() { return name; }

    public void setAge(int age) { this.age = age; }
    public void setName(String name) { this.name = name; }

    @Override
    public String toString() {
        return "name: " + this.name + ", age: " + this.age;
    }
}