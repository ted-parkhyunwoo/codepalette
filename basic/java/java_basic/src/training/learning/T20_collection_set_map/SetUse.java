package training.learning.T20_collection_set_map;
import java.util.HashSet;
import java.util.Objects;

// hashset이 많이 쓰임. 순서보장X 중복허용X
public class SetUse {
    public static void main(String[] args) {
        HashSet<Object> mySet = new HashSet<>();

        // 추가
        mySet.add(2);
        mySet.add("This is a String");
        mySet.add(2.4d);
        System.out.println(mySet);

        // 조회 
        // equals()로 작동해서 값비교 됨. 사용자정의 타입 사용시 eqauls(), hashCode()를 오버라이드 해야함. - 아래 설명
        System.out.println(mySet.contains(2));
        System.out.println(mySet.contains("This is a String"));
        System.out.println(mySet.contains("This is a String."));        // false
        System.out.println(mySet.contains(2.4f));                       // false
        // size()
        System.out.println(mySet.size());                               // 3
        // 반복문은 index기반 사용불가로 범위기반 사용(advanced for)
        for (Object o : mySet) { System.out.println(o); }

        // 수정: 불가. index접근 안됨, 범위기반 for문은 값 수정 불가. hashCode() 또한 수정해야 하기 때문에, 원칙상 불가.
        
        // 삭제
        mySet.remove(2);
        mySet.remove(3213);         // 무시됨
        System.out.println(mySet);

        HashSet<Integer> intSet = new HashSet<>();
        intSet.add(2);
        mySet.add(2);
        System.out.println(mySet);
        mySet.removeAll(intSet);        //  모두삭제 기능 있음.
        System.out.println(mySet);


        // 사용자정의 데이터 사용시 유의사항: hashCode(), eqauls() 오버라이드 해야 값비교가 정확히 됨. Person은 그게 안됨.
        Person p1 = new Person("Ted");
        Person p2 = new Person("Ted");
        Person p3 = new Person(p1);
        HashSet<Person> personSet = new HashSet<>();
        personSet.add(p1);
        personSet.add(p2);
        personSet.add(p3);
        System.out.println(personSet);      //  중복됨.

        // 사용자정의 데이터에 hashCode() 와 equals()를 오버라이드 하여 값비교를 정상적으로 하게 함.
        Person2 q1 = new Person2(p1);
        Person2 q2 = new Person2(p2);
        Person2 q3 = new Person2(p3);
        HashSet<Person2> personSet2 = new HashSet<>();
        personSet2.add(q1);
        personSet2.add(q2);
        personSet2.add(q3);
        System.out.println(personSet2);


        // +@ hashCode()       : 5자리 해시코드로 리턴(int). 모든 객체는 이 hashCode()를 가지고있음.
        String a = "123";
        System.out.println(a.hashCode());

        // +@ getClass() : 모든 객체가 갖고있으며, 실제타입을 return.
        Object t1 = new Person2(q1);
        System.out.println(t1.getClass());
    }
}


// equals, hashCode 재정의 없는 버전. 중복제거가 안됨.
class Person {
    private String name;
    public Person(String name) { this.name = name; }
    public Person(Person obj)  { this.name = obj.name; }

    public String getName() { return this.name; }

    @Override
    public String toString() { return this.name; }
}

// equals, hashCode 재정의 된 버전.
class Person2 {
    private String name;
    public Person2(String name) { this.name = name; }
    public Person2(Person2 obj) { this.name = obj.name; }
    public Person2(Person obj)  { this.name = obj.getName(); }
    public String getName() { return this.name; }

    @Override
    public String toString() { return this.name; }


    /*  hashCode() 와 equals() 재정의.
     이클립스는 우클릭- source- generate hashCode() and equals()... 로 생성. (없음. 시도안해봄)
     intelliJ 에서 alt+insert 혹은 우클릭-생성으로 equals(), hashCode() 재정의 가능.
     vscode에서는 우클릭- 소스작업에 Generate hashCode() and equals()... 있음.
    */


    // 내가 작성한 hashCode() 와 equals() override.
    @Override
    public int hashCode() { return this.name.hashCode(); }
    @Override
    public boolean equals(Object obj) {
        if (obj == this) return true;                               // 최적화용. 없어도 작동은 함.
        if (obj == null) return false;                              //  null일 경우예외처리
        if (obj.getClass() != this.getClass()) return false;        // [필수]실제 타입 비교
        Person2 person2Casting = (Person2) obj;
        // return person2Casting.getName().equals(this.name);          // [필수]실제 값비교    (문제: name이 null인 경우 판별불가)
        return Objects.equals(person2Casting.getName(), this.name);      // 실무에서는 이렇게 쓰임
        //! +@ Objects는 null체크를 위해 추가된 클래스로, 아래 자동생성 버전들이 직접 null 체크 하거나, Objects를 쓰는 이유가 이러함.
        
    }


    // vscode 에서 생성한 버전. 다른 IDE에 비해 조금 더 장황함
    // @Override
    // public int hashCode() {
    //     final int prime = 31;
    //     int result = 1;
    //     result = prime * result + ((name == null) ? 0 : name.hashCode());
    //     return result;
    // }
    // @Override
    // public boolean equals(Object obj) {
    //     if (this == obj)
    //         return true;
    //     if (obj == null)
    //         return false;
    //     if (getClass() != obj.getClass())
    //         return false;
    //     Person2 other = (Person2) obj;
    //     if (name == null) {
    //         if (other.name != null)
    //             return false;
    //     } else if (!name.equals(other.name))
    //         return false;
    //     return true;
    // }

    // [IntelliJ IDEA생성] 현재코드는 name이 private이므로, getName() 사용 가능하도록 "가능한 경우 getter 사용" 체크해야 올바르게 작동
    // @Override
    // public boolean equals(Object o) {
    //     if (o == null || getClass() != o.getClass()) return false;
    //     Person2 person2 = (Person2) o;
    //     return Objects.equals(getName(), person2.getName());
    // }

    // @Override
    // public int hashCode() {
    //     return Objects.hashCode(getName());
    // }


    // 이클립스에서 생성한 버전을 따라 씀 작동결과 같음.
    // @Override
    // public int hashCode() { return Objects.hash(this.name); }

    // @Override
    // public boolean equals(Object obj) {
    //     if (obj == this) return true;
    //     if (obj == null) return false;
    //     if (getClass() != obj.getClass()) return false;
    //     Person2 castingObj = (Person2) obj;
    //     return Objects.equals(name, castingObj.getName());
    // }


    

}