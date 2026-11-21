/**
 * Concrete Decorator: wraps a Beverage and adds soy milk, priced by size (TALL 0.10, GRANDE 0.15, VENTI 0.20).
 */
public class Soy extends CondimentDecorator {
    public Soy(Beverage beverage) {
        this.beverage = beverage;
    }

    // Delegation: wrapped description plus this condiment's name.
    public String getDescription() {
        return beverage.getDescription() + ", Soy";
    }

    // Starts from the wrapped cost; size comes via the forwarded getSize().
    public double cost() {
        double cost = beverage.cost();
        if (beverage.getSize() == Size.TALL) {
            cost += 0.10;
        } else if (beverage.getSize() == Size.GRANDE) {
            cost += 0.15;
        } else if (beverage.getSize() == Size.VENTI) {
            cost += 0.20;
        }
        return cost;
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
