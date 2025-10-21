package training.learning.T12_modifiers;

// Access Modifiers;접근제한자 : public, private, protected 등
// 참고: 패키지 기반의 java설계에서는 protected가 private만큼 캡슐화를 정확히 하기 모호한 부분이 있어, protected는 잘 안쓰이는 모양임.
/* CLASS의 접근제한자:
    class에서는 public과 기본(패키지)만 가능
    class에서는 접근제어자 없을 땐 default(package라고도 함): import가 안됨. 같은 패키지 내(같은 디렉토리)만 사용가능
*/
class ModifireClass2 extends ModifireClass {

/* 변수와 메서드의 접근제한자
    public: 모두 접근 가능. 
    private: 해당 클래스에서만 가능. 
    protected: 상속클래스에서도 가능.
    위 접근제한자 기능은 cpp와 동일.

    상속시 접근제한자 유의사항
    자식클래스는 부모클래스의 접근제한과 같거나 더 넓어야함. 따라서 부모클래스(기본클래스)의 범위가 더 넓고, 자식이 좁다면 오류발생.
    예를들어 Person의 void main() 은 public, SpiderMan의 void main() 은 protected 혹은 private() 시 오류발생
    정리: 기본클래스-좁게. 자식클래스-같거나 넓게.
*/

    // 아래 코드는 상속받은 기본클래스(ModifireClass)와 비교하면서 볼 것.

    // hiding: 변수는 Override가 없다. 사실상 기본클래스의 test2는 "변수숨김"처리되고 아래 코드로 우선참조(포인팅)됨
    protected int test2 = 20; // protected는 기본클래스와 파생클래스의 범위가 같기 때문에 OK.
    // private int test4 = 4;    // 기본클래스는 default. 파생클래스는 private를 쓰기 때문에 오류.
    public int test3 = 30;  // 기본클래스의 test3은 은닉처리되었으나, 파생클래스에서는 직접접근 가능하도록.

    // 변수의 접근제한자와 마찬가지로 메서드에서도 printHey() 접근제한자를 다른것으로 바꾸거나 없애면 오류발생
    @Override
    public void printHey() { System.out.println("HEY!!!"); }



}
