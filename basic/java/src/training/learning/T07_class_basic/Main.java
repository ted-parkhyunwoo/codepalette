package training.learning.T07_class_basic;

public class Main {
    static void statusFb(FishBread fb) {
        String res = fb.index + "번은 " + (fb.baked? "먹음":"안먹음");
        System.out.println(res);
    }
    public static void main(String[] args) {
        // 구체화 과정: 객체들의 속성부여.
        // 객체 선언시 new 클래스(); 식으로 선언됨...
        FishBread fb1 = new FishBread();
        fb1.index = 0;
        fb1.bake();
        statusFb(fb1);

        // 메모리 구조 살펴보기: stack, heap, class영역
        // fb1의 메모리참조는 stack에 저장 -> heap pointing.
        // T07_class와 main은 클래스영역에 저장됨
        FishBread fb2 = new FishBread();
        // 다음 속성부여 과정을 거쳐 index, baked등은 heap에 저장됨.
        fb2.index = 1;
        statusFb(fb2);
    }
}
