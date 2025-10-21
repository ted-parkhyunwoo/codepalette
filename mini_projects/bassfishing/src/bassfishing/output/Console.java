package bassfishing.output;
import bassfishing.utility.*;
import bassfishing.data.Reel;
import bassfishing.units.*;

// 기능클래스(유틸리티클래스) 4개의 멤버메서드는 모두 초기화 없이 static으로 작동한다.
// 멤버변수 또한 static.
public class Console {

    public static final String LENGTH_UNIT = "m";       // 출력문에 쓰일 길이단위. 예: m, 미터, yd, 야드 등.
    public static final int DIFFERENCE_OVER = 6;        // 새로감을 라인 (오차주의)로 출력할 기본라인과의 갭. 6lb 기본값.
    // printOtherLine(Reel reel) 에서 쓰이는 최소/ 최대 라인 lb 기본값.
    public static final int MINIMUM_LB = 4;
    public static final int MAXIMUM_LB = 20;


    // Converter.Line의 console 출력버전.
    public static void printLineConvert(double power, LineUnits unit) {
        String unitStr = unit.equals(LineUnits.LB)? "lb": "호";
        double res = Converter.Line(power, unit);
        System.out.println("LINE: " + power + unitStr + " -> " + res + (unit.equals(LineUnits.LB)? "호": "lb" ));
    }

    // Converter.Sinker의 console 출력버전.
    public static void printSinkerConvert(double weight, SinkerUnits unit) {
        String unitStr = unit == SinkerUnits.G? "g" : "호";
        final String resStr = String.format("%.2f", Converter.Sinker(weight, unit));    // 소수점 두자리까지만 반올림처리
        System.out.println("SINKER: " + weight + unitStr + " -> " + resStr + (unitStr.equals("g")? "호":"g"));
    }    


    // ReelLineCapa.getOtherLineLength console 출력버전.
    public static void printOtherLineLength(Reel reel, double newPower, LineUnits unit) {
        // double -> rounded Strings. 필요에 맞춰 모두 반올림처리됨.
        String newCapaStr = String.format("%.1f",  ReelLineCapa.getOtherLineLength(reel, newPower, unit));
        String newPowerLbStr = unit.equals(LineUnits.LB)? String.format("%.0f", newPower) + "lb" : String.format("%.0f", Converter.Line(newPower, LineUnits.HO)) + "lb";
        String newPowerHoStr = unit.equals(LineUnits.LB)? String.format("%.1f", Converter.Line(newPower, LineUnits.LB)) + "호" : String.format("%.1f", newPower) + "호";

        // string stream for result string
        StringBuilder sb = new StringBuilder();
        sb.append(newPowerHoStr + "-" + newPowerLbStr  + " " + newCapaStr + LENGTH_UNIT);

        // conditionally added text (lb 기준으로 작동함. ho로 입력받은 인스턴스도 상관없이 lb기준으로 작동.)
        boolean isSameUnit = reel.getUnitType().equals(unit);
        boolean isDefaultPower =  isSameUnit? reel.getPower() == newPower: reel.getPower() == Converter.Line(newPower, unit);
        // LB 기준으로 재정의(오차 구하기 위해)
        double basePowerLB = ReelLineCapa.getBasePowerLb(reel);
        double newPowerLB = unit.equals(LineUnits.LB)? newPower: Converter.Line(newPower, LineUnits.HO);
        boolean isDifferenceOver = basePowerLB < newPowerLB - DIFFERENCE_OVER || basePowerLB > newPowerLB + DIFFERENCE_OVER;
        if (isDifferenceOver)       { sb.append(" (오차주의)"); }
        if (isDefaultPower)         { sb.append(" (Base)"); }

        // print result.
        System.out.println(sb);
    }

    // 범위 내 라인(기본값:4 ~ 20lb) 모두 출력
    public static void printOtherLineLength(Reel reel) {
        System.out.println(reel.getName() + ":");
        for (int i = MINIMUM_LB; i <= MAXIMUM_LB; i += 2) {
            System.out.print("  ");
            printOtherLineLength(reel, i, LineUnits.LB);
        }
    }

}
