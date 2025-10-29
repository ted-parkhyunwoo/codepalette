package java_uf;
import java.util.Arrays;

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

}
