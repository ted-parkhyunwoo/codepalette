package training.learning.T13_polymorphism;

public class ParentClass {
    private int age;
    private String name;

    public ParentClass() {}
    public ParentClass(int age, String name) {
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