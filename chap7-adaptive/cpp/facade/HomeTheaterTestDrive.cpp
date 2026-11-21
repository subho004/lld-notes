// Client: builds the subsystem on the stack, then drives it only through the facade.
#include "HomeTheaterFacade.h"

int main() {
    Amplifier amp("Amplifier");
    Tuner tuner("Tuner", amp);
    StreamingPlayer player("Streaming Player");
    Projector projector("Projector");
    TheaterLights lights("Theater Ceiling Lights");
    Screen screen("Theater Screen");
    PopcornPopper popper("Popcorn Popper");

    // The facade stores references, so the components above must outlive it (they do).
    HomeTheaterFacade homeTheater(amp, tuner, player, projector, lights, screen, popper);

    homeTheater.watchMovie("Raiders of the Lost Ark");
    homeTheater.endMovie();
    return 0;
}
