/**
 * Concrete Command: turns the (simple) fan on; undo turns it back off.
 */
public class CeilingFanOnCommand implements Command {
    CeilingFan ceilingFan;

    public CeilingFanOnCommand(CeilingFan ceilingFan) {
        this.ceilingFan = ceilingFan;
    }

    public void execute() {
        ceilingFan.on();
    }

    public void undo() {
        ceilingFan.off();
    }
}
