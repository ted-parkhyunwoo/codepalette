package training.testcodes;
import training.module.Print;

public class HelloWorld {
    public static void main(String[] args) {
        char[] hello = {'H', 'e', 'l', 'l', 'o'};

        for (char c : hello) {
            Print.p(c);
        }

        Print.nextLn();
        Print.ln("World");
    }
}