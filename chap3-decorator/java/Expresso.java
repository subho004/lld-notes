/**
 * Concrete Component: a plain espresso (spelled "Expresso" in this codebase) that decorators can wrap.
 * The has*() flags are unused here; cost() adds only the base price.
 */
public class Expresso extends Beverage {
    public Expresso() {
        description = "Expresso";
    }

    public double cost() {
        return 1.99 + super.cost();
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
