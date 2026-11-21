/**
 * Concrete Decorator: wraps a Beverage and adds Mocha (flat $0.20).
 */
public class Mocha extends CondimentDecorator {
    public Mocha(Beverage beverage) {
        this.beverage = beverage;
    }

    // Delegation: wrapped description plus this condiment's name.
    public String getDescription() {
        return beverage.getDescription() + ", Mocha";
    }

    // Delegation: this condiment's price plus the wrapped drink's cost.
    public double cost() {
        return 0.20 + beverage.cost();
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
