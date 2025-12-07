package training.learning.T15_abstract_class;

public class Child2 extends Parent {
    Child2() { super(2); }

    // @Override 를 생략하는것은 권장하진 않는다. (의도를 명확히 하기 위함)
    public void func() { System.out.println("child2."); }
    public String str() { return "Base: " + Base + ", id: " + id; }
}
