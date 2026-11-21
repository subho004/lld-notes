/**
 * Subject interface of the pattern: observers register, unregister and get notified.
 */
public interface Subject {
    public void registerObserver(Observer o);

    public void removeObserver(Observer o);

    public void notifyObservers();
}
