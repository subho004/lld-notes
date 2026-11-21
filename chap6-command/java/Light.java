/**
 * Receiver: a light that knows how to turn itself on and off.
 */
public class Light {
    String location;

    public Light(String location) {
        this.location = location;
    }

    public Light() {
        this.location = "";
    }

    public void on() {
        System.out.println(location + " Light is on");
    }

    public void off() {
        System.out.println(location + " Light is off");
    }
}
