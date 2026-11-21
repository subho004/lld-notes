package facade;

/** Subsystem component driven by HomeTheaterFacade. */
public class TheaterLights {
    String description;

    public TheaterLights(String description) {
        this.description = description;
    }

    public void on() {
        System.out.println(description + " lights on");
    }

    public void off() {
        System.out.println(description + " lights off");
    }

    public void dim(int level) {
        System.out.println(description + " lights dimmed to " + level + "%");
    }
}
