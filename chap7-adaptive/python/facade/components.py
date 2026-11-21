"""Subsystem classes behind the facade; each only prints what the real device would do."""
class Amplifier:
    """Subsystem component."""

    def __init__(self, description: str) -> None:
        self.description = description

    def on(self) -> None:
        print(f"{self.description} amplifier on")

    def off(self) -> None:
        print(f"{self.description} amplifier off")

    def set_streaming_player(self, player: "StreamingPlayer") -> None:  # string: forward reference, class is defined later
        print(f"{self.description} amplifier streaming player set to {player}")

    def set_volume(self, level: int) -> None:
        print(f"{self.description} amplifier volume set to {level}")


class Tuner:
    """Subsystem component; keeps a reference to the amplifier but the facade never uses it."""

    def __init__(self, description: str, amplifier: Amplifier) -> None:
        self.description = description
        self.amplifier = amplifier

    def on(self) -> None:
        print(f"{self.description} tuner on")

    def off(self) -> None:
        print(f"{self.description} tuner off")

    def set_am_fm(self) -> None:
        print(f"{self.description} tuner set to AM/FM mode")


class StreamingPlayer:
    """Subsystem component; __str__ is the Java toString() used by Amplifier."""

    def __init__(self, description: str) -> None:
        self.description = description

    def on(self) -> None:
        print(f"{self.description} player on")

    def off(self) -> None:
        print(f"{self.description} player off")

    def play(self, movie: str) -> None:
        print(f'{self.description} player playing "{movie}"')

    def stop(self) -> None:
        print(f"{self.description} player stopped")

    def __str__(self) -> str:
        return f"{self.description} Streaming Player"


class Projector:
    """Subsystem component."""

    def __init__(self, description: str) -> None:
        self.description = description

    def on(self) -> None:
        print(f"{self.description} projector on")

    def off(self) -> None:
        print(f"{self.description} projector off")

    def wide_screen_mode(self) -> None:
        print(f"{self.description} projector in widescreen mode (16x9 aspect ratio)")


class TheaterLights:
    """Subsystem component."""

    def __init__(self, description: str) -> None:
        self.description = description

    def on(self) -> None:
        print(f"{self.description} lights on")

    def off(self) -> None:
        print(f"{self.description} lights off")

    def dim(self, level: int) -> None:
        print(f"{self.description} lights dimmed to {level}%")


class Screen:
    """Subsystem component."""

    def __init__(self, description: str) -> None:
        self.description = description

    def up(self) -> None:
        print(f"{self.description} screen going up")

    def down(self) -> None:
        print(f"{self.description} screen going down")


class PopcornPopper:
    """Subsystem component."""

    def __init__(self, description: str) -> None:
        self.description = description

    def on(self) -> None:
        print(f"{self.description} popper on")

    def off(self) -> None:
        print(f"{self.description} popper off")

    def pop(self) -> None:
        print(f"{self.description} popper popping popcorn!")
