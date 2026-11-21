import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Composite: holds Quackables (ducks or other Flocks) and treats them uniformly as one Quackable.
 */
public class Flock implements Quackable {
    List<Quackable> ducks = new ArrayList<Quackable>();

    public void add(Quackable duck) {
        ducks.add(duck);
    }

    // Delegates to every child; child flocks recurse.
    public void quack() {
        Iterator<Quackable> iterator = ducks.iterator();
        while (iterator.hasNext()) {
            Quackable duck = iterator.next();
            duck.quack();
        }
    }

    // Registers the observer on each child so it is told about every individual duck, not the flock.
    public void registerObserver(Observer observer) {
        Iterator<Quackable> iterator = ducks.iterator();
        while (iterator.hasNext()) {
            Quackable duck = iterator.next();
            duck.registerObserver(observer);
        }
    }

    // Intentionally empty: each child duck notifies its own observers when it quacks.
    public void notifyObservers() {
    }
}
