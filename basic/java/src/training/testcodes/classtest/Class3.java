package training.testcodes.classtest;

// class3는 class1를 계승하고 height 라는 정보를 추가를 담는다

public class Class3 extends Class1 {
    private float height;

    // 생성자 오버로딩.
    public Class3() {}
    public Class3(int age, String name, float height) {
        super(age, name);
        //!! super는 생성자의 반드시 첫줄에 있어야 작동.
        this.height = height;
    }

    public void setHeight(float height) { this.height = height; }
    public float getHeight() { return this.height; }

    @Override
    public String toString() {
        // String format 사용해보기. (c-style)
        return String.format("name: %s, age: %d, height: %.2f", getName(), getAge(), height);
    }


}
