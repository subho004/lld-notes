/**
 * Invoker: holds on/off Command slots and the last-used command for undo.
 * It knows only the Command interface, never the receivers.
 */
public class RemoteControl {
    Command[] onCommands;
    Command[] offCommands;
    Command undoCommand;

    public RemoteControl() {
        onCommands = new Command[7];
        offCommands = new Command[7];
        Command noCommand = new NoCommand();
        undoCommand = noCommand;
        for (int i = 0; i < 7; i++) {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }
    }

    public void setCommand(int slot, Command onCommand, Command offCommand) {
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }

    // Remember the command before running it so undoButtonWasPushed() can reverse it.
    public void onButtonWasPushed(int slot) {
        undoCommand = onCommands[slot];
        onCommands[slot].execute();
    }

    public void offButtonWasPushed(int slot) {
        undoCommand = offCommands[slot];
        offCommands[slot].execute();
    }

    public void undoButtonWasPushed() {
        undoCommand.undo();
    }

    // Prints each slot's command class names via getClass().getName().
    public String toString() {
        StringBuffer stringBuff = new StringBuffer();
        stringBuff.append("\n------ Remote Control ------\n");
        for (int i = 0; i < onCommands.length; i++) {
            stringBuff.append("[slot " + i + "] " + onCommands[i].getClass().getName() + "    "
                    + offCommands[i].getClass().getName() + "\n");
        }
        return stringBuff.toString();
    }
}
