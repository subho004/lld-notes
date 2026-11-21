/**
 * Macro Command (Composite-like): a Command that executes a whole array of commands.
 */
public class MacroCommand implements Command {
    Command[] commands;

    public MacroCommand(Command[] commands) {
        this.commands = commands;
    }

    public void execute() {
        for (Command command : commands) {
            command.execute();
        }
    }

    // Undo runs in reverse order so the last action is reversed first.
    public void undo() {
        for (int i = commands.length - 1; i >= 0; i--) {
            commands[i].undo();
        }
    }
}
