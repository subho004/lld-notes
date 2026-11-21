/**
 * Concrete Quackable (leaf): a redhead that goes "Quack".
 * Observer support is delegated to a helper Observable owned by the duck.
 */
public class RedheadDuck implements Quackable {
    // Helper that holds the observers; the duck passes itself so observers see the real source.
    Observable observable;

    public RedheadDuck() {
        observable = new Observable(this);
    }

    // Quack, then tell registered observers.
    public void quack() {
        System.out.println("Quack");
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
        return "Redhead Duck";
    }
}
