package training.learning.T07_class_basic;

// 추상화: 클래스생성과정.
public class FishBread {
    // Member vars.
    int index;
    boolean baked;

    // Member methods.
    void flip() {
        System.out.println("붕어빵 뒤집음.");
    }
    void bake() {
        baked = false;
        for(int i = 0; i < 4; ++i) {
            flip();
        }
        baked = true;
        System.out.println("붕어빵 다 구움.");
    }
}
