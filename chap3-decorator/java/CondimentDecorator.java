/**
 * Decorator base: is-a Beverage (same type as the component) and has-a Beverage
 * (the wrapped drink). Concrete decorators delegate to it and add their part.
 */
public abstract class CondimentDecorator extends Beverage {
    // The wrapped component (a plain drink or another decorator).
    Beverage beverage;

    public abstract String getDescription();

    // Re-declared abstract, so every decorator must implement these flags.
    public abstract boolean hasMilk();

    public abstract boolean hasSoy();

    public abstract boolean hasMocha();

    public abstract boolean hasWhip();

    // Forwards to the wrapped drink so the size set on the base drink is
    // visible through any number of decorator layers (Soy prices by size).
    public Size getSize() {
        return beverage.getSize();
    }
}
