package facade;

/** Subsystem component driven by HomeTheaterFacade. */
public class Projector {
    String description;

    public Projector(String description) {
        this.description = description;
    }

    public void on() {
        System.out.println(description + " projector on");
    }

    public void off() {
        System.out.println(description + " projector off");
    }

    public void wideScreenMode() {
        System.out.println(description + " projector in widescreen mode (16x9 aspect ratio)");
    }
}
