package training.learning.T14_dynamic_bind;

public class Child extends Parent{
    private int x = 2;
    public void func() { System.out.println("자식입니다."); }   // 명시하지 않아도 override함.
    @Override
    public String str() { return "Child" + x; }
    
}
