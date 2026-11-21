/** Context: holds its fly/quack behaviors (composition) and delegates to them. */
public abstract class Duck {
    // Strategy references; package-private so subclasses can pick their own in constructors.
    FlyBehavior flyBehavior;
    QuackBehavior quackBehavior;

    // Default strategies; subclasses may override them in their own constructors.
    public Duck() {
        this.flyBehavior = new FlyWithWings();
        this.quackBehavior = new Quack();
    }

    public abstract void display();

    // Delegates to the current strategy instead of implementing flying here.
    public void performFly() {
        flyBehavior.fly();
    }

    public void performQuack() {
        quackBehavior.quack();
    }

    public void swim() {
        System.out.println("All ducks float, even decoys!");
    }

    // Setters allow swapping the algorithm at runtime.
    public void setFlyBehavior(FlyBehavior fb) {
        flyBehavior = fb;
    }
    public void setQuackBehavior(QuackBehavior qb) {
        quackBehavior = qb;
    }

}