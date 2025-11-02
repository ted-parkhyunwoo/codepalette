package training.learning.T13_polymorphism;

public class ChildClass extends ParentClass {
    private float height;

    public ChildClass() {}
    public ChildClass(int age, String name, float height) {
        super(age, name);
        this.height = height;
    }

    public void setHeight(float height) { this.height = height; }
    public float getHeight() { return this.height; }

    public void sayHello() {
        System.out.println("Hello");
    }

    @Override
    public String toString() {
        return String.format("name: %s, age: %d, height: %.2f", getName(), getAge(), height);
    }


}
