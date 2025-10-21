package bassfishing;
import bassfishing.utility.*;
import bassfishing.data.Reel;
import bassfishing.output.Console;
import bassfishing.units.*;

public class example {
    
    // println 단축을위한 메서드 제네릭
    public static <T>void println(T t) { System.out.println(t); }

    public static void main(String[] args) {
        // ! Converter.* 변환 주의: 두번 째 매개변수는 현재 단위를 넣음
        println(Converter.Sinker(3, SinkerUnits.HO));               // 11.25        싱커 호수<->gram 상호 변환기
        println(Converter.Line(4, LineUnits.HO));                   // 16.0         라인 호수<->lb 상호 변환기

        // output.Console 쉬운출력
        Console.printSinkerConvert(14, SinkerUnits.G);              // SINKER: 14.0g -> 3.73호
        Console.printSinkerConvert(4.5, SinkerUnits.HO);            // SINKER: 4.5호 -> 16.88g
        Console.printLineConvert(12, LineUnits.LB);                 // LINE: 12.0lb -> 3.0호
        Console.printLineConvert(1.5, LineUnits.HO);                // LINE: 1.5호 -> 6.0lb



        // LineUnits.LB등을 LB로 단축하기 위한 선언: 참고) Sinker도 HO를 쓰므로 주의.
        LineUnits LB = LineUnits.LB, HO = LineUnits.HO;

        // getOtherLineLength 를 Reel객체 없이 쓸 때 (기본라인, 기본라인단위, 기본라인길이, 새 라인, 새 라인 유닛) -> 새 라인 길이
        println(ReelLineCapa.getOtherLineLength(12, LB, 100, 4, HO));           // 75.0     (12LB 100m 감기는 릴 4호로 바꾸면)
        // 라인의 타입이 같다면 생략 가능.
        println(ReelLineCapa.getOtherLineLength(12, 100, 16));                  // 75.0         12lb -> 16lb
        println(ReelLineCapa.getOtherLineLength(3.5, 100, 2.5));                // 140.0        3.5호 -> 2.5호


        // Reel 데이터클래스 초기화
        Reel myZillion21 = new Reel("21질리언", 14, LB, 90);        // myZillion21 은 14 lb 90m 감기는 릴
        Reel iWant = new Reel("21SteezLtd", 3.5, HO, 85);
        // Reel 객체 조회
        println(myZillion21);                                       // Name: 21질리언  LineCapa: 14.0lb 90.0
        println(iWant.getName());                                   // 21SteezLtd


        // 릴 기본제원 권사량을 베이스로 다른 라인 권사량 추정. getOtherLineLength(Reel객체, 새 라인, 새 라인 유닛)
        println(ReelLineCapa.getOtherLineLength(myZillion21, 12, LB));      // 105.0    (12lb로 바꾸면)
        println(ReelLineCapa.getOtherLineLength(myZillion21, 3.5, HO));     // 90.0     (3.5호로 바꾸면)


        // output.Console 쉬운출력
        Console.printOtherLineLength(myZillion21, 10, LB);              // 2.5호-10lb 126.0m
        Console.printOtherLineLength(iWant, 2.5, HO);                   // 2.5호-10lb 119.0m
        Console.printOtherLineLength(myZillion21);                      // 6 ~ 20lb 모두 출력
        Console.printOtherLineLength(iWant);
    }
}
