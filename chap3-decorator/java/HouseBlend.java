/**
 * Concrete Component: a plain House Blend coffee that decorators can wrap.
 * The has*() flags are unused here; cost() adds only the base price.
 */
public class HouseBlend extends Beverage {
    public HouseBlend() {
        description = "House Blend Coffee";
    }

    public double cost() {
        return 0.89 + super.cost();
    }

    public boolean hasMilk() {
        return false;
    }

    public boolean hasSoy() {
        return false;
    }

    public boolean hasMocha() {
        return false;
    }

    public boolean hasWhip() {
        return false;
    }
}
