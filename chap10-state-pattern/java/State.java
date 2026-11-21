/** State interface: one method per action the context can receive; each concrete state implements its own behavior. */
public interface State {

    void insertQuarter();

    void ejectQuarter();

    void turnCrank();

    void dispense();

    void refill();
}
