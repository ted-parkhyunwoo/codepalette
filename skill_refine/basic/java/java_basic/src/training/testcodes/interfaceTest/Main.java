package training.testcodes.interfaceTest;

// interface 와 implements에 대한 예제.
public class Main {
    public static void main(String[] args) {
        Animal myChicken = new Chicken("꼬돌이");
        Animal[] myAnimals = {new Dog("우유"), myChicken, new Chicken(myChicken)};
        for (Animal e : myAnimals) {
            if (Animal.isAnimal) {
                System.out.println("이름: " + e.getName());
                e.move();
                e.bark();
            }
        }
    }
}
