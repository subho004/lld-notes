package facade;

/** Client: builds the subsystem, hands it to the facade, then uses only the facade. */
public class HomeTheaterTestDrive {
    public static void main(String[] args) {
        Amplifier amp = new Amplifier("Amplifier");
        Tuner tuner = new Tuner("Tuner", amp);
        StreamingPlayer player = new StreamingPlayer("Streaming Player");
        Projector projector = new Projector("Projector");
        TheaterLights lights = new TheaterLights("Theater Ceiling Lights");
        Screen screen = new Screen("Theater Screen");
        PopcornPopper popper = new PopcornPopper("Popcorn Popper");

        HomeTheaterFacade homeTheater = new HomeTheaterFacade(amp, tuner, player, projector, lights, screen,
                popper);

        homeTheater.watchMovie("Raiders of the Lost Ark");
        homeTheater.endMovie();
    }
}
