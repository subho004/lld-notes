/**
 * Concrete Command that wraps two Runnables (lambdas), so no per-action command class is needed.
 */
public class LambdaCommand implements Command {
    private Runnable executeAction;
    private Runnable undoAction;

    public LambdaCommand(Runnable executeAction, Runnable undoAction) {
        this.executeAction = executeAction;
        this.undoAction = undoAction;
    }

    public void execute() {
        executeAction.run();
    }

    public void undo() {
        undoAction.run();
    }
}
