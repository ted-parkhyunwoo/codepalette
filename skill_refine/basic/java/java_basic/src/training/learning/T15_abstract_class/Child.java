package training.learning.T15_abstract_class;

public class Child extends Parent {
    // 생성자를 통한 blank final변수 id 에 할당.
    Child() { super(1); }

    // abstract클래스를 계승하는 구체클래스는 @Override를 생략하여 구현해도 가능은 하다.(Child2 참고.)
    @Override
    public void func() { System.out.println("child1."); }
    @Override
    public String str() { return "Base: " + Base + ", id: " + id; }
}
