/**
 * Observer interface of the pattern. Push variant: the subject passes the measurements as arguments.
 */
public interface Observer {
    public void update(float temperature, float humidity, float pressure);
}
