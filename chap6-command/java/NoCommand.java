/**
 * Null Object: does nothing, used to fill empty slots so the remote never null-checks.
 */
public class NoCommand implements Command {
    public void execute() {
    }

    public void undo() {
    }
}
