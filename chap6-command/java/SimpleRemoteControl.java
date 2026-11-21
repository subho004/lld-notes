/**
 * Invoker with a single Command slot; the simplest form of the pattern.
 */
public class SimpleRemoteControl {
    Command slot;

    public SimpleRemoteControl() {
    }

    public void setCommand(Command command) {
        slot = command;
    }

    public void buttonWasPressed() {
        slot.execute();
    }

    public void undoButtonWasPressed() {
        slot.undo();
    }
}
