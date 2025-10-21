package bassfishing.utility;
import bassfishing.data.Reel;
import bassfishing.units.LineUnits;

public class ReelLineCapa {
    // reel의 line power를 항상 lb단위로만 필요시 변환 후 return.
    static public double getBasePowerLb(Reel reel) {
        if (reel.getUnitType().equals(LineUnits.HO))
            return Converter.Line(reel.getPower(), LineUnits.HO);
        return reel.getPower();
    }

    // 같은 타입으로만 작동하는 권사량 계산 코어. (base라인과 new라인의 UnitType이 둘다 ho거나 lb거나)
    static public double getOtherLineLength(double basePower, double baseLength, double newPower) {
        return baseLength * (basePower / newPower);
    }

    // 아래는 타입 혹은 객체를 매개변수를 받는 경우의 오버로딩.

    // 다른 타입으로도 확장 가능하게 함. 매개변수에 reel 인스턴스 없이 쓰는 경우
    static public double getOtherLineLength(double basePower, LineUnits baseUnit, double baseLength, double targetPower, LineUnits targetUnit) {
        if (baseUnit.equals(targetUnit))
            return getOtherLineLength(basePower, baseLength, targetPower);
        if (baseUnit.equals(LineUnits.LB))
            return getOtherLineLength(basePower, baseLength, Converter.Line(targetPower, LineUnits.HO));
        else
            return getOtherLineLength(basePower, baseLength, Converter.Line(targetPower, LineUnits.LB));
    }

    // 오버로딩: 릴 객체를 받아 쓰는 경우.
    static public double getOtherLineLength(Reel reel, double targetPower, LineUnits targetUnit) {
        double basePower = reel.getPower();
        double baseLength = reel.getLength();
        LineUnits baseUnit = reel.getUnitType();
        return getOtherLineLength(basePower, baseUnit, baseLength, targetPower, targetUnit);
    }
}


