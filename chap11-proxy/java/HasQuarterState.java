import java.util.Random;

/** Concrete State: a quarter is in the machine and the crank has not been turned yet. */
public class HasQuarterState implements State {
    private static final long serialVersionUID = 2L;
    // transient: the context is not serialized along with the state.
    transient GumballMachine gumballMachine;
    // Seeded from the clock, so the 1-in-10 winner draw differs between runs.
    Random randomWinner = new Random(System.currentTimeMillis());

    public HasQuarterState(GumballMachine gumballMachine) {
        this.gumballMachine = gumballMachine;
    }

    public void insertQuarter() {
        System.out.println("You can't insert another quarter");
    }

    public void ejectQuarter() {
        System.out.println("Quarter returned");
        gumballMachine.setState(gumballMachine.getNoQuarterState());
    }

    public void turnCrank() {
        System.out.println("You turned...");
        // Roughly 10% chance of a winner, and only if at least 2 gumballs remain.
        int winner = randomWinner.nextInt(10);
        if (winner == 0 && gumballMachine.getCount() > 1) {
            gumballMachine.setState(gumballMachine.getWinnerState());
        } else {
            gumballMachine.setState(gumballMachine.getSoldState());
        }
    }

    public void dispense() {
        System.out.println("No gumball dispensed");
    }

    public void refill() {
    }

    public String toString() {
        return "waiting for turn of crank";
    }
}
