package bassfishing.data;
import bassfishing.units.LineUnits;

public class Reel {
    // basic info
    private final String name;
    private final double power;
    private final double lineLength;
    private final LineUnits unit;
    
    public Reel(String name, double power, LineUnits unit, double lineLength) {
        this.name = name;
        this.power = power;
        this.lineLength = lineLength;
        this.unit = unit;
    }
    
    public String getName()     { return this.name; }
    public double getPower()    { return this.power; }
    public LineUnits getUnitType() { return this.unit; }
    public double getLength()   { return this.lineLength; }

    @Override
    public String toString() {
        return "Name: " + this.name + "  LineCapa: " + power + (this.unit.equals(LineUnits.LB)? "lb " : "호 ") + lineLength;
    }
}
