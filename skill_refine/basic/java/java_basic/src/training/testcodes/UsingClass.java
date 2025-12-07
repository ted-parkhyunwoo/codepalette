package training.testcodes;
import training.testcodes.classtest.Class1;
import training.testcodes.classtest.Class2;
import training.testcodes.classtest.Class3;

public class UsingClass {

    public static void main(String[] args) {
        Class1 c1 = new Class1();
        Class1 c2 = new Class1(24, "lala");
        c1.setAge(32);
        c1.setName("lulu");
        System.out.println(c1);
        System.out.println(c2);

        Class2 c3 = Class2.getInstance();
        int sz = 5;
        int[] tmp = c3.getArray(sz);
        c3.printArray(tmp);
        System.out.println(c3);

        Class3 c4 = new Class3();
        Class3 c5 = new Class3(24, "luke", 182.3f);
        c4.setAge(42);
        c4.setName("petter");
        c4.setHeight(172.323f);

        System.out.println(c4);
        System.out.println(c5);

    }
}
