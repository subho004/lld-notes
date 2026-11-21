/**
 * Concrete Quackable (leaf): a rubber duck that goes "Squeak".
 * Observer support is delegated to a helper Observable owned by the duck.
 */
public class RubberDuck implements Quackable {
    // Helper that holds the observers; the duck passes itself so observers see the real source.
    Observable observable;

    public RubberDuck() {
        observable = new Observable(this);
    }

    // Quack, then tell registered observers.
    public void quack() {
        System.out.println("Squeak");
        notifyObservers();
    }

    // Delegation: the duck forwards observer handling to its Observable.
    public void registerObserver(Observer observer) {
        observable.registerObserver(observer);
    }

    public void notifyObservers() {
        observable.notifyObservers();
    }

    public String toString() {
        return "Rubber Duck";
    }
}
