package facade;

/** Subsystem component driven by HomeTheaterFacade. */
public class PopcornPopper {
    String description;

    public PopcornPopper(String description) {
        this.description = description;
    }

    public void on() {
        System.out.println(description + " popper on");
    }

    public void off() {
        System.out.println(description + " popper off");
    }

    public void pop() {
        System.out.println(description + " popper popping popcorn!");
    }
}
