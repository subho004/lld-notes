import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 * Subject interface for the remote proxy. The RMI stub implements it too, so the monitor
 * cannot tell a local machine from a remote one. Each method must declare RemoteException.
 */
public interface GumballMachineRemote extends Remote {
    public int getCount() throws RemoteException;

    public String getLocation() throws RemoteException;

    public State getState() throws RemoteException;
}
