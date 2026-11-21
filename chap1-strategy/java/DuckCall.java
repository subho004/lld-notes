/** Uses a QuackBehavior on its own, without being a Duck: strategies are reusable. */
public class DuckCall {
    QuackBehavior quackBehavior;

    public DuckCall() {
        quackBehavior = new Quack();
    }

    // Delegates to the strategy.
    public void performQuack() {
        quackBehavior.quack();
    }

    public void setQuackBehavior(QuackBehavior qb) {
        quackBehavior = qb;
    }
}
