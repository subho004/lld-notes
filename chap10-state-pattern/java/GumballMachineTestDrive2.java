/**
 * Demo driver for the State-based GumballMachine2. Output contains State@hash text
 * and may include a random WinnerState bonus ball.
 */
public class GumballMachineTestDrive2 {

    public static void main(String[] args) {
        GumballMachine2 gumballMachine = new GumballMachine2(5);
        System.out.println(gumballMachine);

        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        System.out.println(gumballMachine);

        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        System.out.println(gumballMachine);

        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        System.out.println(gumballMachine);

        System.out.println("--- Refilling ---");
        gumballMachine.refill(5);
        System.out.println(gumballMachine);

        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        System.out.println(gumballMachine);
    }
}
