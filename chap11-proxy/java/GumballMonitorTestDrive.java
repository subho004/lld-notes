import java.rmi.Naming;

/** Client driver: looks up remote machines by name via RMI; needs rmiregistry and running machine JVMs. */
public class GumballMonitorTestDrive {
    public static void main(String[] args) {
        String[] locations = { "santafe", "boulder", "seattle" };

        if (args.length > 0) {
            locations = args;
        }

        GumballMonitor[] monitors = new GumballMonitor[locations.length];

        for (int i = 0; i < locations.length; i++) {
            try {
                // lookup() returns the stub (proxy), cast to the remote interface.
                GumballMachineRemote machine = (GumballMachineRemote) Naming.lookup("//localhost/" + locations[i]);
                monitors[i] = new GumballMonitor(machine);
                // Prints GumballMonitor@<identity hash>; varies per run.
                System.out.println(monitors[i]);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        for (int i = 0; i < monitors.length; i++) {
            if (monitors[i] != null) {
                monitors[i].report();
                System.out.println();
            }
        }
    }
}
