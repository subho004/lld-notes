package facade;

/** Subsystem component driven by HomeTheaterFacade (not used by its movie methods). */
public class Tuner {
    String description;
    Amplifier amplifier;

    public Tuner(String description, Amplifier amplifier) {
        this.description = description;
        this.amplifier = amplifier;
    }

    public void on() {
        System.out.println(description + " tuner on");
    }

    public void off() {
        System.out.println(description + " tuner off");
    }

    public void setAmFm() {
        System.out.println(description + " tuner set to AM/FM mode");
    }
}
