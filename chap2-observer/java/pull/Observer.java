package pull;

/**
 * Observer interface of the pattern. Pull variant: no arguments, observers query the subject.
 */
public interface Observer {
    public void update();
}
