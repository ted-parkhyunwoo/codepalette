package training.learning.T14_dynamic_bind;

public class Parent {
    private int x = 1;
    public void func() { System.out.println("부모입니다."); }
    public String str() {
        return "Parent" + x;
    }
}
