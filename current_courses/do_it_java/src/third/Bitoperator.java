package third;

public class Bitoperator {
    public static void main(String[] args) {
        // 반전: ~
        int num1 = 10;      // 00001010
        int res = ~num1;    // 11110101

        // &(and): 둘다 1일때만 1. 아니면 0
        int num5 = 5;       // 00000101
        int num10 = 10;     // 00001010
        res = num5 & num10; // 00000000

        // |(or): 둘중에 하나만 1이여도 1
        res = num5 | num10; // 00001111   ->    15
        System.out.println(res);

        // ^(xor): 서로 다르면1, 같으면 0
        res = num5 ^ num10; // 00001111

        // << 비트를 좌측으로 이동: 한칸 이동마다 x2(2칸-x4, 3칸-x8)
        res = num5 << 2;    // 00000101     ->      00010100
        System.out.println(res);    // 2의 x승 만큼 곱함
        // >> 비트를 우측으로 이동: 한칸 이동마다 /2
        res = num10 >> 2;   // 00001010     ->      00000010(나머진 버림)
        System.out.println(res);    // 2의 x승 만큼 나눔


    }
}
