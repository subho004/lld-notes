"""Client: builds the subsystem once, then drives it only through the facade."""
from components import (Amplifier, PopcornPopper, Projector, Screen,
                        StreamingPlayer, TheaterLights, Tuner)
from home_theater_facade import HomeTheaterFacade


def main() -> None:
    amp = Amplifier("Amplifier")
    tuner = Tuner("Tuner", amp)
    player = StreamingPlayer("Streaming Player")
    projector = Projector("Projector")
    lights = TheaterLights("Theater Ceiling Lights")
    screen = Screen("Theater Screen")
    popper = PopcornPopper("Popcorn Popper")

    home_theater = HomeTheaterFacade(amp, tuner, player, projector, lights, screen, popper)

    home_theater.watch_movie("Raiders of the Lost Ark")
    home_theater.end_movie()


if __name__ == "__main__":
    main()
