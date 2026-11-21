"""Receivers: the objects that actually do the work (Light, CeilingFan, ...)."""


class Light:
    """Receiver: knows how to switch a light; has no knowledge of commands."""

    def __init__(self, location: str = "") -> None:
        self.location = location

    def on(self) -> None:
        print(self.location + " Light is on")

    def off(self) -> None:
        print(self.location + " Light is off")


class CeilingFan:
    def __init__(self, location: str) -> None:
        self.location = location

    def on(self) -> None:
        print(self.location + " ceiling fan is on")

    def off(self) -> None:
        print(self.location + " ceiling fan is off")


class CelingFanv2:
    """Receiver with speed state (name misspelling kept from the original repo)."""

    HIGH = 3
    MEDIUM = 2
    LOW = 1
    OFF = 0

    def __init__(self, location: str) -> None:
        self.location = location
        self.speed = CelingFanv2.OFF

    def high(self) -> None:
        self.speed = CelingFanv2.HIGH
        print(self.location + " ceiling fan is on high")

    def medium(self) -> None:
        self.speed = CelingFanv2.MEDIUM
        print(self.location + " ceiling fan is on medium")

    def low(self) -> None:
        self.speed = CelingFanv2.LOW
        print(self.location + " ceiling fan is on low")

    def off(self) -> None:
        self.speed = CelingFanv2.OFF
        print(self.location + " ceiling fan is off")

    def get_speed(self) -> int:
        return self.speed


class Stereo:
    def __init__(self, location: str = "") -> None:
        self.location = location

    def on(self) -> None:
        print(self.location + " Stereo is on")

    def off(self) -> None:
        print(self.location + " Stereo is off")

    def set_cd(self) -> None:
        print(self.location + " Stereo is set for CD input")

    def set_dvd(self) -> None:
        print(self.location + " Stereo is set for DVD input")

    def set_radio(self) -> None:
        print(self.location + " Stereo is set for radio input")

    def set_volume(self, volume: int) -> None:
        print(self.location + " Stereo volume is set to " + str(volume))


class GarageDoor:
    def __init__(self, location: str = "") -> None:
        self.location = location

    def up(self) -> None:
        print(self.location + " Garage Door is Open")

    def down(self) -> None:
        print(self.location + " Garage Door is Closed")

    def stop(self) -> None:
        print(self.location + " Garage Door is Stopped")

    def light_on(self) -> None:
        print(self.location + " Garage Door light is on")

    def light_off(self) -> None:
        print(self.location + " Garage Door light is off")
