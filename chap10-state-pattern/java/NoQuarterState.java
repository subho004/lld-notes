/** Concrete State: waiting for a quarter. Initial state when the machine has stock. */
public class NoQuarterState implements State {
    GumballMachine2 gumballMachine;

    public NoQuarterState(GumballMachine2 gumballMachine) {
        this.gumballMachine = gumballMachine;
    }

    public void insertQuarter() {
        System.out.println("You inserted a quarter");
        gumballMachine.setState(gumballMachine.getHasQuarterState()); // change state to HasQuarterState
    }

    public void ejectQuarter() {
        System.out.println("You haven't inserted a quarter");
    }

    public void turnCrank() {
        System.out.println("You turned, but there's no quarter");
    }

    public void dispense() {
        System.out.println("You need to pay first");
    }

    public void refill() {
    }
}
