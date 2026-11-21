// HomeTheaterFacade: Facade giving one simple interface to the home theater subsystem.
#pragma once
#include <string>

#include "Components.h"

// One simple interface over the whole subsystem. The facade holds references:
// the components are owned by the caller (main) and outlive the facade.
class HomeTheaterFacade {
public:
    HomeTheaterFacade(Amplifier& amp, Tuner& tuner, StreamingPlayer& player, Projector& projector,
                      TheaterLights& lights, Screen& screen, PopcornPopper& popper)
        : amp(amp), tuner(tuner), player(player), projector(projector),
          lights(lights), screen(screen), popper(popper) {}

    // Facade method: one call orchestrates the whole startup sequence across the subsystem.
    void watchMovie(const std::string& movie) {
        std::cout << "Get ready to watch a movie...\n";
        popper.on();
        popper.pop();
        lights.dim(10);
        screen.down();
        projector.on();
        projector.wideScreenMode();
        amp.on();
        amp.setStreamingPlayer(player);
        amp.setVolume(5);
        player.on();
        player.play(movie);
    }

    // Reverse of watchMovie: shuts the components down in a sensible order.
    void endMovie() {
        std::cout << "Shutting movie theater down...\n";
        popper.off();
        lights.on();
        screen.up();
        projector.off();
        amp.off();
        player.stop();
        player.off();
    }

private:
    Amplifier& amp;
    [[maybe_unused]] Tuner& tuner;  // kept for parity with the Java; unused here
    StreamingPlayer& player;
    Projector& projector;
    TheaterLights& lights;
    Screen& screen;
    PopcornPopper& popper;
};
