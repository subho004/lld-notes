/**
 * Observer interface: called whenever an observed duck quacks.
 */
public interface Observer {
    public void update(QuackObservable duck);
}
