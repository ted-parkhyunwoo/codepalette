package t08abstract.abstractclass;

public class MyNoteBook extends NoteBook {
    // 구체클래스: 추상메서드 들을 무조건 다 구현해야함.
    @Override
    public void typing() {
        System.out.println("MyNoteBook typing()");
    }

    // NoteBook 추상클래스에서 구현 됐지만, 재정의 가능
    @Override
    public void display() {
        System.out.println("MyNoteBook display()");
    }
}
