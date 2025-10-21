package training.testcodes;
import training.module.Rand;
import training.module.Print;

public class UseRand {
    public static void main(String[] args) {
        for (int i = 0; i < 100; i++) {
            Print.p(Rand.randint(5));
        }
        Print.nextLn();
        Print.ln(Rand.randint(1, 6));

        for (int i = 0; i < 10; i++) {
            Print.ln(Rand.randint());
        }
    }
}
