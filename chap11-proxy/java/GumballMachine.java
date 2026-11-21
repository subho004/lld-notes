import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

/**
 * Real subject for the remote proxy and Context for the State pattern. Extends UnicastRemoteObject,
 * so RMI exports it and hands remote clients a generated stub (the actual proxy).
 */
public class GumballMachine extends UnicastRemoteObject implements GumballMachineRemote {
    private static final long serialVersionUID = 2L;

    // One shared instance of every state; the machine switches between them via setState().
    State soldOutState;
    State noQuarterState;
    State hasQuarterState;
    State soldState;
    State winnerState;

    State state;
    int count = 0;
    String location;

    public GumballMachine(String location, int numberGumballs) throws RemoteException {
        soldOutState = new SoldOutState(this);
        noQuarterState = new NoQuarterState(this);
        hasQuarterState = new HasQuarterState(this);
        soldState = new SoldState(this);
        winnerState = new WinnerState(this);
        this.count = numberGumballs;
        this.location = location;
        if (numberGumballs > 0) {
            state = noQuarterState;
        } else {
            state = soldOutState;
        }
    }

    // Context delegates every action to the current state object.
    public void insertQuarter() {
        state.insertQuarter();
    }

    public void ejectQuarter() {
        state.ejectQuarter();
    }

    // dispense() is called separately because turning the crank is not itself a state-changing "dispense".
    public void turnCrank() {
        state.turnCrank();
        state.dispense();
    }

    public void refill(int count) {
        this.count += count;
        System.out.println("The gumball machine was just refilled; its new count is: " + this.count);
        state.refill();
    }

    // Package-private: only the state classes drive transitions.
    void setState(State state) {
        this.state = state;
    }

    void releaseBall() {
        System.out.println("A gumball comes rolling out the slot...");
        if (count > 0) {
            count = count - 1;
        }
    }

    public String getLocation() {
        return location;
    }

    public int getCount() {
        return count;
    }

    // Returned over RMI, so State is Serializable (state objects hold a transient back-reference).
    public State getState() {
        return state;
    }

    public State getSoldOutState() {
        return soldOutState;
    }

    public State getNoQuarterState() {
        return noQuarterState;
    }

    public State getHasQuarterState() {
        return hasQuarterState;
    }

    public State getSoldState() {
        return soldState;
    }

    public State getWinnerState() {
        return winnerState;
    }

    public String toString() {
        StringBuffer result = new StringBuffer();
        result.append("\nMighty Gumball, Inc.");
        result.append("\nJava-enabled Standing Gumball Model #2004");
        result.append("\nInventory: " + count + " gumball");
        if (count != 1) {
            result.append("s");
        }
        result.append("\nMachine is " + state + "\n");
        return result.toString();
    }
}
