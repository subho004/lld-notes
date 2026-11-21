/**
 * Concrete Decorator: wraps a Beverage and adds whipped cream (flat $0.10).
 */
public class Whip extends CondimentDecorator {
    public Whip(Beverage beverage) {
        this.beverage = beverage;
    }

    // Delegation: wrapped description plus this condiment's name.
    public String getDescription() {
        return beverage.getDescription() + ", Whip";
    }

    // Delegation: this condiment's price plus the wrapped drink's cost.
    public double cost() {
        return 0.10 + beverage.cost();
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
