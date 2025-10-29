import java.math.BigInteger;

//! 단순 순열/조합의 공식 계산이지, 파이썬 코드처럼 실제로 줄을 세우진 못하는 상태.
public class Permutation {

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

    // 팩토리얼을 쓰지 않는 새로운 함수
    public static BigInteger permute(int n, int r) {
        BigInteger res = BigInteger.valueOf(1);
        int tmp = n - r;
        for (int i = n; i > tmp; --i) {
            res = res.multiply(BigInteger.valueOf(i));
        }

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
        System.out.println(getFactorial(20));
        System.out.println(getPermute(5, 3));
        System.out.println(permute(100, 100));
        System.out.println(getCombs(5, 3));
    }
}
