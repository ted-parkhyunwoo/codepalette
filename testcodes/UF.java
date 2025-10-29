import java.util.Arrays;

// class my {
//     static <T> void print(T t) { System.out.println(t); }
// }

public class UF {
    private final int size;
    private int[] node;

    public UF(int size) {
        this.size = size;
        this.node = new int[size];
        for (int i = 0; i < this.size; ++i) this.node[i] = i;
    }

    public int find(int n) {
        if (n != node[n]) {
            this.node[n] = find(this.node[n]);
        }
        return this.node[n];
    }

    public void union(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            this.node[b] = rootA;
        }
    }

    public boolean isConnect(int a, int b) { return find(a) == find(b); }

    @Override
    public String toString() {
        return Arrays.toString(this.node);
    }

    // main test
    // public static void main(String[] args) {
    //     UF a = new UF(5);
    //     a.union(0, 3);
    //     a.union(3, 2);
    //     a.union(4, 0);
    //     my.print(a.isConnect(0, 2));
    //     my.print(a.isConnect(1, 0));
    //     my.print(a);
    // }
}
