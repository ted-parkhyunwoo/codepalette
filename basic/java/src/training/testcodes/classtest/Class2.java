package training.testcodes.classtest;

// singleton class.
// 한개의 인스턴스만 가짐. 입력받은 sz만큼의 배열을 생성하고, 배열을 프린트하고(어떤int[]든), 최근 배열을 저장해 toString() 하는 기능. 다 연관도 그닥 없고 쓰잘데기 없지만 예제임.

public class Class2 {
    private static Class2 instance = new Class2();
    public static Class2 getInstance() { return instance; }
    
    private Class2() {
        // 외부에서 인스턴스 생성 막는 용도로 private생성자 만듬.
    }

    // 최근사용배열: 접근제한자는 어차피 하나의 인스턴스이므로 static필요X.
    private int[] lastArr = {};
    
    public int[] getArray(int size) {
        int[] res = new int[size];
        lastArr = res;
        return res;
    }

    public void printArray(int[] arr) {
        int sz = arr.length;
        if (sz <= 0) return;
        System.out.print("[" + arr[0]);
        for (int i = 1; i < sz; ++i) {
            System.out.print(", " + arr[i]);
        }
        System.out.println(']');
    }

    @Override
    public String toString() {
        if (lastArr == null || lastArr.length == 0) return "[]\n";

        // StringBuilder 를 사용하면 String 에 += 식으로 매 객체를 생성하는것보다 자원이 절약됨. std::stringstream 같은 역할.
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        sb.append(lastArr[0]);
        for (int i = 1; i < lastArr.length; ++i) {
            sb.append(", ").append(lastArr[i]);
        }
        sb.append("]\n");
        return sb.toString();
    }
    
}
