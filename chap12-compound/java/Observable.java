import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Helper (Observer pattern subject): stores observers and notifies them on behalf of a duck.
 * Composition lets each duck reuse this instead of repeating the logic.
 */
public class Observable implements QuackObservable {
    List<Observer> observers = new ArrayList<Observer>();
    QuackObservable duck;

    public Observable(QuackObservable duck) {
        this.duck = duck;
    }

    public void registerObserver(Observer observer) {
        observers.add(observer);
    }

    // Passes the owning duck (not this helper) to each observer.
    public void notifyObservers() {
        Iterator<Observer> iterator = observers.iterator();
        while (iterator.hasNext()) {
            Observer observer = iterator.next();
            observer.update(duck);
        }
    }
}
