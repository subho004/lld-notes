/**
 * Command interface: the only type the invokers (remote controls) know about.
 * execute() performs the request on a receiver; undo() reverses it.
 */
public interface Command {
    public void execute();

    public void undo();
}
