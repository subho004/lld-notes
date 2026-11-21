/**
 * Receiver: ceiling fan with speed levels. The filename/class spelling "Celing" is kept as in the original repo.
 * Speed is tracked so commands can read it via getSpeed() for undo.
 */
public class CelingFanv2 {
    public static final int HIGH = 3;
    public static final int MEDIUM = 2;
    public static final int LOW = 1;
    public static final int OFF = 0;

    String location;
    int speed;

    public CelingFanv2(String location) {
        this.location = location;
    }

    public void high() {
        speed = HIGH;
        System.out.println(location + " ceiling fan is on high");
    }

    public void medium() {
        speed = MEDIUM;
        System.out.println(location + " ceiling fan is on medium");
    }

    public void low() {
        speed = LOW;
        System.out.println(location + " ceiling fan is on low");
    }

    public void off() {
        speed = OFF;
        System.out.println(location + " ceiling fan is off");
    }

    // Lets commands snapshot the current state before changing it.
    public int getSpeed() {
        return speed;
    }
}
