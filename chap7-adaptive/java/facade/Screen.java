package facade;

/** Subsystem component driven by HomeTheaterFacade. */
public class Screen {
    String description;

    public Screen(String description) {
        this.description = description;
    }

    public void up() {
        System.out.println(description + " screen going up");
    }

    public void down() {
        System.out.println(description + " screen going down");
    }
}
