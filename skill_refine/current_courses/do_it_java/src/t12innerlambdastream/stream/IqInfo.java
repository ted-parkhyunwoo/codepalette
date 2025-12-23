package t12innerlambdastream.stream;

public class IqInfo {
    private String name;
    private int iq;
    private int age;

    public IqInfo(String name, int iq, int age) {
        this.name = name;
        this.iq = iq;
        this.age = age;
    }

    public String getName() { return name; }
    public int getAge() { return age; }
    public int getIq() { return iq; }

    @Override
    public String toString() {
        return "이름: " + name + " 나이: " + age + " IQ: " + iq;
    }

}
