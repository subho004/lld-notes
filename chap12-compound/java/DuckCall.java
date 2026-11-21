/**
 * Concrete Quackable (leaf): a duck call that goes "Kwak".
 * Observer support is delegated to a helper Observable owned by the duck.
 */
public class DuckCall implements Quackable {
    // Helper that holds the observers; the duck passes itself so observers see the real source.
    Observable observable;

    public DuckCall() {
        observable = new Observable(this);
    }

    // Quack, then tell registered observers.
    public void quack() {
        System.out.println("Kwak");
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
        return "Duck Call";
    }
}
