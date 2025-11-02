package training.learning.T10_inheritance;

public class Person {
    String name;
    void move(){
        System.out.println("사람이동");
    }

    public Person() {
        this.name = "Empty";
    }

    public Person(String name) {
        this.name = name;
    }
}

