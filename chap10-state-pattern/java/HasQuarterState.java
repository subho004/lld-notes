import java.util.Random;

/** Concrete State: a quarter is inserted; turning the crank goes to Sold or (randomly) Winner. */
public class HasQuarterState implements State {
    GumballMachine2 gumballMachine;
    // Time-seeded, so a 1-in-10 winner makes runs non-reproducible.
    Random randomWinner = new Random(System.currentTimeMillis());

    public HasQuarterState(GumballMachine2 gumballMachine) {
        this.gumballMachine = gumballMachine;
    }

    public void insertQuarter() {
        System.out.println("You can't insert another quarter");
    }

    public void ejectQuarter() {
        System.out.println("Quarter returned");
        gumballMachine.setState(gumballMachine.getNoQuarterState());
    }

    // Transition: 10% chance of WinnerState, only if more than one gumball remains.
    public void turnCrank() {
        System.out.println("You turned...");
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
}
