/**
 * Decorator: wraps a Quackable, adds quack counting, and forwards everything else to it.
 */
public class QuackCounter implements Quackable {
    Quackable duck;
    // Static: one shared total across all counted ducks.
    static int numberOfQuacks;

    public QuackCounter(Quackable duck) {
        this.duck = duck;
    }

    // Delegate first, then add the counting behaviour.
    public void quack() {
        duck.quack();
        numberOfQuacks++;
    }

    public static int getQuacks() {
        return numberOfQuacks;
    }

    // Forwarded to the wrapped duck so observers still hear it.
    public void registerObserver(Observer observer) {
        duck.registerObserver(observer);
    }

    public void notifyObservers() {
        duck.notifyObservers();
    }
}
