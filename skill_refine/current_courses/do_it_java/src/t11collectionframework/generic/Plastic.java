package t11collectionframework.generic;

public class Plastic implements Material{

    @Override
    public void doPrinting() {
        System.out.println("Plastic 으로 출력");
    }

    @Override
    public String toString() {
        return "Material: Plastic";
    }
}
