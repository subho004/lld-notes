/**
 * Concrete Command: opens the door; undo closes it. Identical to GarageDoorOpenCommand.
 */
public class GarageDoorUpCommand implements Command {
    GarageDoor garageDoor;

    public GarageDoorUpCommand(GarageDoor garageDoor) {
        this.garageDoor = garageDoor;
    }

    public void execute() {
        garageDoor.up();
    }

    public void undo() {
        garageDoor.down();
    }
}
