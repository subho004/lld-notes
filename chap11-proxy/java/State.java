import java.io.Serializable;

/** State interface: one method per action the machine can receive. Serializable so it can cross RMI. */
public interface State extends Serializable {
    void insertQuarter();

    void ejectQuarter();

    void turnCrank();

    void dispense();

    void refill();
}
