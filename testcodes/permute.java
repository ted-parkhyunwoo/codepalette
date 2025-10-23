import java.math.BigInteger;
import java.util.ArrayList;

public class permute {

    public static BigInteger getFactorial(int num) {
        BigInteger res = new BigInteger("1");
        for (int i = num; i > 1; --i) {
            res = res.multiply(BigInteger.valueOf(i));
        }
        return res;
    }

    // n개중 r개
    // permute = n! / (n - r)!
    // combination = n! / r!(n - r)!

    public static BigInteger getPermute(int n, int r) {
        BigInteger nFac = getFactorial(n);
        BigInteger nsubrFac = getFactorial(n - r);
        BigInteger res = nFac.divide(nsubrFac);
        return res;
    }

    public static BigInteger getCombs(int n, int r) {
        BigInteger nFac = getFactorial(n);
        BigInteger nsubrFac = getFactorial(n - r);
        nsubrFac = nsubrFac.multiply(getFactorial(r));
        BigInteger res = nFac.divide(nsubrFac);
        return res;
    }

    public static void main(String[] args) {
        int[] myArray = {3, 1, 4, 1, 5};
        System.out.println(getFactorial(20));
        System.out.println(getPermute(5, 3));
        System.out.println(getCombs(5, 3));
    }
}
