"""Concrete commands: each binds a receiver to an action (and its undo)."""
from command import Command
from devices import CeilingFan, CelingFanv2, GarageDoor, Light, Stereo


class LightOnCommand(Command):
    """Concrete command; receiver is a Light, undo does the opposite action."""

    def __init__(self, light: Light) -> None:
        self.light = light

    def execute(self) -> None:
        self.light.on()

    def undo(self) -> None:
        self.light.off()


class LightOffCommand(Command):
    def __init__(self, light: Light) -> None:
        self.light = light

    def execute(self) -> None:
        self.light.off()

    def undo(self) -> None:
        self.light.on()


class CeilingFanOnCommand(Command):
    def __init__(self, ceiling_fan: CeilingFan) -> None:
        self.ceiling_fan = ceiling_fan

    def execute(self) -> None:
        self.ceiling_fan.on()

    def undo(self) -> None:
        self.ceiling_fan.off()


class CeilingFanOffCommand(Command):
    def __init__(self, ceiling_fan: CeilingFan) -> None:
        self.ceiling_fan = ceiling_fan

    def execute(self) -> None:
        self.ceiling_fan.off()

    def undo(self) -> None:
        self.ceiling_fan.on()


class _CeilingFanSpeedCommand(Command):  # leading underscore: internal base, not for clients
    """Shared undo logic (the Java classes each repeat it): restore the previous speed."""

    def __init__(self, ceiling_fan: CelingFanv2) -> None:
        self.ceiling_fan = ceiling_fan
        self.prev_speed = 0

    def undo(self) -> None:
        if self.prev_speed == CelingFanv2.HIGH:
            self.ceiling_fan.high()
        elif self.prev_speed == CelingFanv2.MEDIUM:
            self.ceiling_fan.medium()
        elif self.prev_speed == CelingFanv2.LOW:
            self.ceiling_fan.low()
        else:
            self.ceiling_fan.off()


class CeilingFanHighCommand(_CeilingFanSpeedCommand):
    def execute(self) -> None:
        # Save the current speed first so undo() can restore it.
        self.prev_speed = self.ceiling_fan.get_speed()
        self.ceiling_fan.high()


class CeilingFanMediumCommand(_CeilingFanSpeedCommand):
    def execute(self) -> None:
        self.prev_speed = self.ceiling_fan.get_speed()
        self.ceiling_fan.medium()


class CeilingFanLowCommand(_CeilingFanSpeedCommand):
    def execute(self) -> None:
        self.prev_speed = self.ceiling_fan.get_speed()
        self.ceiling_fan.low()


class CeilingFanv2OffCommand(_CeilingFanSpeedCommand):
    def execute(self) -> None:
        self.prev_speed = self.ceiling_fan.get_speed()
        self.ceiling_fan.off()


class GarageDoorOpenCommand(Command):
    def __init__(self, garage_door: GarageDoor) -> None:
        self.garage_door = garage_door

    def execute(self) -> None:
        self.garage_door.up()

    def undo(self) -> None:
        self.garage_door.down()


class GarageDoorUpCommand(GarageDoorOpenCommand):
    # Identical to GarageDoorOpenCommand in the Java; subclassed so type(x).__name__ still differs.
    pass


class GarageDoorDownCommand(Command):
    def __init__(self, garage_door: GarageDoor) -> None:
        self.garage_door = garage_door

    def execute(self) -> None:
        self.garage_door.down()

    def undo(self) -> None:
        self.garage_door.up()


class StereoOnWithCDCommand(Command):
    def __init__(self, stereo: Stereo) -> None:
        self.stereo = stereo

    def execute(self) -> None:
        # One command driving several receiver calls.
        self.stereo.on()
        self.stereo.set_cd()
        self.stereo.set_volume(11)

    def undo(self) -> None:
        self.stereo.off()


class StereoOffCommand(Command):
    def __init__(self, stereo: Stereo) -> None:
        self.stereo = stereo

    def execute(self) -> None:
        self.stereo.off()

    def undo(self) -> None:
        self.stereo.on()
