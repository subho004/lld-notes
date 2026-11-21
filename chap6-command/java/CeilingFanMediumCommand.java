/**
 * Concrete Command with undo: remembers the previous fan speed in execute() so undo() can restore it.
 */
public class CeilingFanMediumCommand implements Command {
    CelingFanv2 ceilingFan;
    int prevSpeed;

    public CeilingFanMediumCommand(CelingFanv2 ceilingFan) {
        this.ceilingFan = ceilingFan;
    }

    public void execute() {
        prevSpeed = ceilingFan.getSpeed();
        ceilingFan.medium();
    }

    // Undo = restore the speed saved by execute(); falls back to off for any other value.
    public void undo() {
        if (prevSpeed == CelingFanv2.HIGH) {
            ceilingFan.high();
        } else if (prevSpeed == CelingFanv2.MEDIUM) {
            ceilingFan.medium();
        } else if (prevSpeed == CelingFanv2.LOW) {
            ceilingFan.low();
        } else {
            ceilingFan.off();
        }
    }
}
