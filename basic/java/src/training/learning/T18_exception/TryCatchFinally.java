package training.learning.T18_exception;

// 메인함수부터 읽으면 됨. 거꾸로 클래스 및 메서드를 찾아갈 것.
// 사용자 정의 예외 처리 예제는 ch18/CustomExceptionTest.java가 훌륭함. 이후 커스텀 할 의지 있으면 시도해 볼것.


// 상속(파생)받아 재정의 하는 경우는 throws객체가 상위예외를 가질 수 없다(컴파일타임 예외 한정). 런타임예외는 생략가능할뿐더러, 파생클래스가 상위예외를 가져도 정상작동됨.
import java.io.IOException;
class Parent {
    public void func() throws IOException {}
}
class Child extends Parent {
    @Override
    public void func() throws IOException {}     // 파생객체에서 재정의시 throws에 예외 상위클래스 Exception 등을 넣으면 컴파일 오류.
}


public class TryCatchFinally {
    
    // 메서드 throws. 예측가능한 예외임을 경고, 처리할 코드를 catch에서 작성하도록 강제유도. 런타임예외는 자동 throws됨.
    // 참고로 static 하지 않으면 try안에선 못씀. 이게 싫다면 TryCatchFinally 클래스객체를 내부에서 생성하고 객체.func로 호출.
    public static void func(int[] arr) { System.out.println(arr[0]); }  // unchecked exception은 throws 하지 않아도 자동으로 throws
    public static void func2() throws ClassNotFoundException { Class.forName("name"); } // checked exception은 직접 throws 하지않으면 컴파일X


    public static void main(String[] args) {

        try {
            // 아래 주석처리된 예외발생문에 사용해볼 객체들.
            int[] arr = {1};
            String str = new String("try에서 생성된 문자열객체");
            int[] myArray = null;

            // 하나씩 주석해제하며 사용해 볼 것(try 코드블록에서 모든 예외를 처리하지 않고 catch로 넘어감.)
            // System.out.println(arr[1]);     // ArrayIndexOutOfBoundsException: unchecked exception 발생코드
            // func(myArray);                  // 런타임 메서드 throws -> NullPointerException 발생코드
            // func2();                     // 컴파일타임 메서드 throws -> ClassNotFoundException: exception(checked exception) 발생코드.
            // Class.forName("name");            // ClassNotFoundException: exception(checked exception) 발생코드.

        } 
        // 런타임 예외들
        catch (NullPointerException e) {      // 참고: 객체.printStackTrace() 는 예외문 출력.
            System.out.println("널포인터 예외처리됨.");
            e.printStackTrace();
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("배열접근범위초과예외 처리됨.");
            e.printStackTrace();
        } 

        //! 컴파일타임 예외: ClassNotFoundException 예외처리 과정을 보려면 func2 와 Class.forName() 을 활성화 하고 아래 catch문 주석해제할 것.
        /*  //! 중요. func2와 Class.forName() 사용시: Java에서는 '컴파일타임 예외클래스'를 catch로 적을 수 없음. - Exception에선 처리 가능. 
        catch (ClassNotFoundException e) {   // checked exception: 컴파일 타임에 미리 경고되며, 처리하지 않으면 컴파일되지않음.
            e.printStackTrace();        // 예외경고문이 장황하나, 사실상 마지막줄만 해당됨.
        } 
        */
        
        catch (Exception e) {   // catch문 순서에 주의. 예외 최상위인 Exception이 catch의 처음으로 가면 문제여지가 많음.
            System.out.println("나머지 모든 예외처리.");        
            e.printStackTrace();
        } finally {
            // finally는 str, myArray등의 할당공간 명시적으로 회수: finally없이 예외발생시 회수 안될수 있음.
            System.out.println("try에서 할당된 자원 환원 완료");
        }
    }
}
