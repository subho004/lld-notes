"""HomeTheaterFacade: Facade giving one simple interface to the home theater subsystem."""
from components import (Amplifier, PopcornPopper, Projector, Screen,
                        StreamingPlayer, TheaterLights, Tuner)


class HomeTheaterFacade:
    """One simple interface over the whole home theater subsystem."""

    def __init__(self, amp: Amplifier, tuner: Tuner, player: StreamingPlayer,
                 projector: Projector, lights: TheaterLights, screen: Screen,
                 popper: PopcornPopper) -> None:
        self.amp = amp
        self.tuner = tuner
        self.player = player
        self.projector = projector
        self.lights = lights
        self.screen = screen
        self.popper = popper

    def watch_movie(self, movie: str) -> None:
        # Facade method: one call orchestrates the whole startup sequence across the subsystem.
        print("Get ready to watch a movie...")
        self.popper.on()
        self.popper.pop()
        self.lights.dim(10)
        self.screen.down()
        self.projector.on()
        self.projector.wide_screen_mode()
        self.amp.on()
        self.amp.set_streaming_player(self.player)
        self.amp.set_volume(5)
        self.player.on()
        self.player.play(movie)

    def end_movie(self) -> None:
        # Reverse of watch_movie: shuts the components down in a sensible order.
        print("Shutting movie theater down...")
        self.popper.off()
        self.lights.on()
        self.screen.up()
        self.projector.off()
        self.amp.off()
        self.player.stop()
        self.player.off()
