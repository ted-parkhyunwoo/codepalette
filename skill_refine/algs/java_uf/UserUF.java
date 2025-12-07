package java_uf;
import java.util.ArrayList;


public class UserUF {
    private User users[];
    private UF uf;

    UserUF(User[] arr) {
        this.users = arr;
        int size = arr.length;
        uf = new UF(size);
    }

    // 나이별로 union.
    public void age(){
        uf = new UF(this.users.length);
        for (int i = 0; i < this.users.length - 1; ++i) {
            for (int j = i + 1; j < this.users.length; ++j) {
                User last = users[i];
                User current = users[j];
                int lastGen = last.getAge() / 10;
                int currentGen = current.getAge() / 10;
                if (lastGen == currentGen) {
                    uf.union(i, j);
                }
            }
        }
    }

    // 특정유저로 users에서의 인덱스 찾기. (실패시 -1)
    protected int findIdx(User u) {
        for (int i = 0; i < this.users.length; ++i) {
            if (u.equals(users[i])) return i;
        }
        return -1;
    }

    public boolean isFriend(User a, User b) {
        int aIdx = findIdx(a);
        int bIdx = findIdx(b);
        return this.uf.isConnect(aIdx, bIdx);
    }

    public void printFriends(User u) {
        int uIdx = findIdx(u);
        if (uIdx ==  -1) return;
        int peopleCount = users.length;
        ArrayList<Integer> friendsIdxs = new ArrayList<>();
        for (int i = 0; i < peopleCount; ++i) {
            if (uIdx == i) continue;
            if (uf.isConnect(uIdx, i)) friendsIdxs.add(i);
        }
        
        for (Integer i : friendsIdxs) {
            System.out.println(users[i].getName());
        }
    }



    @Override
    public String toString(){
        return this.uf.toString();
    }

}