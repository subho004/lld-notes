/**
 * Subject interface for the Observer pattern: something that can be observed.
 */
public interface QuackObservable {
    public void registerObserver(Observer observer);

    public void notifyObservers();
}
