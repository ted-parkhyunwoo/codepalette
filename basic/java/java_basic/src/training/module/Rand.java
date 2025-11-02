package training.module;
import java.util.Random;

public class Rand {
    // Random객체 생성
    private static final Random rand = new Random();

    // 0 or 1
    public static int randint() { return rand.nextInt(2); }
    // 0 부터 max - 1 까지
    public static int randint(int max) { return rand.nextInt(max); }
    // min 부터 max 까지
    public static int randint(int min, int max) {
        // 인자 오류시 예외객체 던지기.
        if (min > max) throw new IllegalArgumentException("min should be <= max");
        return rand.nextInt(max - min + 1) + min;
    }

    // true or false
    public static boolean randbool() { return rand.nextBoolean(); }

}
