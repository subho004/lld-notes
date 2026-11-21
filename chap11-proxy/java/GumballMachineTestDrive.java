import java.rmi.Naming;

/** Server side: creates a machine and binds it in the RMI registry (rmiregistry must be running). */
public class GumballMachineTestDrive {
    public static void main(String[] args) {
        GumballMachine gumballMachine = null;
        int count = 0;

        if (args.length < 2) {
            System.out.println("GumballMachine <name> <inventory>");
            System.exit(1);
        }

        try {
            count = Integer.parseInt(args[1]);
            gumballMachine = new GumballMachine(args[0], count);
            Naming.rebind("//localhost/" + args[0], gumballMachine);
            System.out.println("Gumball machine bound at //localhost/" + args[0]);
            System.out.println(gumballMachine);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
