package facade;

/** Subsystem component driven by HomeTheaterFacade. */
public class Amplifier {
    String description;

    public Amplifier(String description) {
        this.description = description;
    }

    public void on() {
        System.out.println(description + " amplifier on");
    }

    public void off() {
        System.out.println(description + " amplifier off");
    }

    public void setStreamingPlayer(StreamingPlayer player) {
        System.out.println(description + " amplifier streaming player set to " + player);
    }

    public void setVolume(int level) {
        System.out.println(description + " amplifier volume set to " + level);
    }
}
