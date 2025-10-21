package bassfishing.utility;
import bassfishing.units.LineUnits;
import bassfishing.units.SinkerUnits;

public class Converter {
    public static double Line(double power, LineUnits unit) {
        switch(unit) {
            case HO: 
                return power * 4;
            case LB: 
                return power / 4;  
        }

        System.err.println("LINE UNIT TYPE ERROR.");
        return -1;
    }

    public static double Sinker(double weight, SinkerUnits unit) {
        switch(unit) {
            case G: 
                return weight / 3.75;
            case HO: 
                return weight * 3.75;
        }
        
        System.err.println("SINKER UNIT TYPE ERROR.");
        return -1;
    }


}
