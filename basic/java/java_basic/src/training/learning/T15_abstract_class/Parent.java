package training.learning.T15_abstract_class;

public abstract class Parent {
    // final 변수 : 불변보장. 상수처리처럼 한번 할당된 것은 수정할 수 없다.(런타임 상수. const는 컴파일타임상수)
    protected final String Base = "Parent";

    // blank final 변수. 초기화블록이나 생성자블록 안에서 한번은 할당(대입) 해야함.
    protected final int id;
    public Parent(int id) { this.id = id; }     // 생성자블록을 통한 할당. Child에서 super(int id) 식으로 할당한다.

    // blank final static 변수: static초기화블록에서 한번 할당 가능.
    protected final static int test;
    static { test = 2; }

    // final 메서드키워드는 override 불가.
    public final void fam() { System.out.println("가족입니다."); }

    // abstract 메서드 키워드는 순수가상함수 작성처럼 구현을 세미콜론; 으로 대체한다.
    public abstract void func();
    public abstract String str();
}
