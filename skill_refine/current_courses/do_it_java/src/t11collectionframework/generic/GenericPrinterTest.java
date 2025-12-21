package t11collectionframework.generic;

public class GenericPrinterTest {
    public static void main(String[] args) {
        // 강의와 다르게 생성자를 material로 받을수 있도록 했으므로 다음과 같이 둘다 사용 가능
        GenericPrinter<Powder> powderPrinter = new GenericPrinter<>();
        GenericPrinter<Plastic> plasticPrinter = new GenericPrinter<>(new Plastic());

        powderPrinter.setMaterial(new Powder());

        // doPrinting()의 래퍼 테스트
        powderPrinter.print();
        plasticPrinter.print();

        // toString() 의 래퍼 테스트
        System.out.println(powderPrinter);
        System.out.println(plasticPrinter);


//        GenericPrinter<Water> waterPrinter = new GenericPrinter<>();
//        waterPrinter.print();

    }
}
