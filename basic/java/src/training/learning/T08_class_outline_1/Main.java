package training.learning.T08_class_outline_1;

public class Main {
    public static void main(String[] args) {
        Chars monster1 = new Chars("피그미");
        Chars monster2 = new Chars();
        monster2.name = "언데드";
        monster2.type = 'E';
        monster2.hp = 120;
        monster2.strength = 17;

        Chars Boss = new Chars("김상철", 'A', 300, 50);

        monster1.printStatus();
        monster2.printStatus();
        Boss.printStatus();

        Boss.kill(monster1);
        monster1.printStatus();
        Boss.printStatus();


    }
}
