/**
 * Component: common type for plain drinks and for the condiment decorators
 * that wrap them, so either can be used wherever a Beverage is expected.
 */
public abstract class Beverage {
    String description = "Unknown Beverage";
    // Package-private so subclasses in this package can set it directly.
    Size size = Size.TALL;

    public Size getSize() {
        return size;
    }

    public void setSize(Size size) {
        this.size = size;
    }

    // Adds the legacy per-condiment surcharges; subclasses add their base price on top.
    // Decorators override this entirely and delegate inward instead.
    public double cost() {
        double condimentCost = 0;
        if (hasMilk()) {
            condimentCost += 0.10;
        }
        if (hasSoy()) {
            condimentCost += 0.15;
        }
        if (hasMocha()) {
            condimentCost += 0.20;
        }
        if (hasWhip()) {
            condimentCost += 0.25;
        }
        return condimentCost;
    }

    public abstract boolean hasMilk();

    public abstract boolean hasSoy();

    public abstract boolean hasMocha();

    public abstract boolean hasWhip();

    // Decorators call this on the wrapped beverage and append their own name.
    public String getDescription() {
        return size + " " + description;
    }

}
