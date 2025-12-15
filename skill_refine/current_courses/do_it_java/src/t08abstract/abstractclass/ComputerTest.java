package t08abstract.abstractclass;

public class ComputerTest {
    public static void main(String[] args) {
        Computer test = new MyNoteBook();
        Computer test2 = new Desktop();
        // 다음과 같이 추상클래스의 미구현 추상메서드를 구체화 가능
        Computer test3 = new NoteBook() {
            @Override
            public void typing() {
                System.out.println("즉시 오버라이드한 노트북 클래스 typing()");
            }
        };

        Computer[] myComputers = {test, test2, test3};

        for (Computer c : myComputers) {
            System.out.println("\n시나리오 시작");
            c.turnOn();
            c.display();
            c.typing();
            c.turnOff();
        }

    }
}
