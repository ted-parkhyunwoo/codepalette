package t11collectionframework.generic;

public class Powder implements Material{

    @Override
    public void doPrinting() {
        System.out.println("Powerder 로 출력");
    }

    @Override
    public String toString() {
        return "Material: Powder";
    }

}
