/**
 * Concrete Component: a plain Dark Roast coffee that decorators can wrap.
 * The has*() flags are unused here; cost() adds only the base price.
 */
public class DarkRoast extends Beverage {

    public DarkRoast() {
        description = "Dark Roast Coffee";
    }

    public double cost() {
        return 0.99 + super.cost();
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
