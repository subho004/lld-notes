package facade;

/** Subsystem component driven by HomeTheaterFacade. */
public class StreamingPlayer {
    String description;

    public StreamingPlayer(String description) {
        this.description = description;
    }

    public void on() {
        System.out.println(description + " player on");
    }

    public void off() {
        System.out.println(description + " player off");
    }

    public void play(String movie) {
        System.out.println(description + " player playing \"" + movie + "\"");
    }

    public void stop() {
        System.out.println(description + " player stopped");
    }

        // Used by Amplifier.setStreamingPlayer when it prints the connected player.
    public String toString() {
        return description + " Streaming Player";
    }
}
