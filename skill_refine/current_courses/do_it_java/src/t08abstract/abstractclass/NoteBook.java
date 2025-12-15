package t08abstract.abstractclass;

public abstract class NoteBook extends Computer {
    // 구체클래스이면서 추상클래스: 구체는 무조건 한개만 상속 가능
    // 추상클래스가 추상클래스를 상속 가능. 일부만 구현 가능. override도 가능.
    // idea: 빨간줄 뜰때 우클릭-임플리먼트 메서드 누르면 아래 비어있는 메서드 자동채워짐
    @Override
    public void display() {
        System.out.println("Notebook display()");
    }


}
