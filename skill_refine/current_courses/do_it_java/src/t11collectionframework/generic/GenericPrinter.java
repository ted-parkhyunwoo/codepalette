package t11collectionframework.generic;

// 시나리오: 3d프린터가 Plastic, Powder 등의 T 재료들이며, T에따라 print, toString 등이 다르게 표현되도록 함.

//! 제네릭 타입에 대한 extends Material 로 제한:
// Material 이라는 인터페이스 혹은 추상클래스를 상속/구현한 타입만 사용 가능하도록 제한
// Water는 Material을 구현한 구현체가 아니므로, GenericPrinter의 타입으로 사용불가

// 참고: 강의에서는 Material이 추상클래스이나, interface로 했으며, 이 경우에도 T extends임.(implements 아님)
public class GenericPrinter<T extends Material> {
    private T material;


    public GenericPrinter() {}

    public GenericPrinter(T material) {
        this.material = material;
    }

    // getter, setter

    public void setMaterial(T material) {
        this.material = material;
    }

    public T getMaterial() {
        return material;
    }


    @Override
    public String toString() {
        return "GenericPrinter: " + material.toString();
    }

    public void print() {

        System.out.print("GenericPrinter: ");

        // doPrinting()은 현재 GenericPrinter가 <T extends Material> 하면서 사용가능해짐
        // T에 대한 제한이 없으면 Object로 인식하므로 Material tmp = (Material) material 등으로 캐스팅 해야함
        material.doPrinting();
    }

    //! +@ 따라서 제네릭에 대한 extends 범위제한의 기능은
    // 1. 통제된 타입(클래스)만 Generic을 쓸 수 있게 제한. (Water를 사용못하게함)
    // 2. 인터페이스, 추상클래스를 쓰도록 유도하여 T로 사용될 클래스들의 재사용성 구조화 강요(Plastic, Powder가 구현/구체로 작성)
    // 3. Generic 클래스 내부에서 T 가 Object가 아닌 특정 interface, abstract로 범위 축소(print()예제참고)

}
