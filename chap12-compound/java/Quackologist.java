/**
 * Concrete Observer: reports each quack of the ducks it is registered with.
 */
public class Quackologist implements Observer {
    public void update(QuackObservable duck) {
        System.out.println("Quackologist: " + duck + " just quacked.");
    }
}
