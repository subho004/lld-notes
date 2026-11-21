"""Client demo: creates receivers and commands, loads RemoteControl slots, runs a macro."""
from command import Command, MacroCommand
from commands import (CeilingFanHighCommand, CeilingFanOffCommand, CeilingFanOnCommand,
                      CeilingFanv2OffCommand, GarageDoorDownCommand, GarageDoorUpCommand,
                      LightOffCommand, LightOnCommand, StereoOffCommand, StereoOnWithCDCommand)
from devices import CeilingFan, CelingFanv2, GarageDoor, Light, Stereo
from remote_control import RemoteControl


def main() -> None:
    remote_control = RemoteControl()

    living_room_light = Light("Living Room")
    kitchen_light = Light("Kitchen")
    ceiling_fan = CeilingFan("Living Room")
    ceiling_fan_v2 = CelingFanv2("Living Room")
    garage_door = GarageDoor("Garage")
    stereo = Stereo("Living Room")

    living_room_light_on = LightOnCommand(living_room_light)
    living_room_light_off = LightOffCommand(living_room_light)
    kitchen_light_on = LightOnCommand(kitchen_light)
    kitchen_light_off = LightOffCommand(kitchen_light)

    ceiling_fan_on = CeilingFanOnCommand(ceiling_fan)
    ceiling_fan_off = CeilingFanOffCommand(ceiling_fan)

    ceiling_fan_high = CeilingFanHighCommand(ceiling_fan_v2)
    ceiling_fan_v2_off = CeilingFanv2OffCommand(ceiling_fan_v2)

    garage_door_up = GarageDoorUpCommand(garage_door)
    garage_door_down = GarageDoorDownCommand(garage_door)

    stereo_on_with_cd = StereoOnWithCDCommand(stereo)
    stereo_off = StereoOffCommand(stereo)

    remote_control.set_command(0, living_room_light_on, living_room_light_off)
    remote_control.set_command(1, kitchen_light_on, kitchen_light_off)
    remote_control.set_command(2, ceiling_fan_on, ceiling_fan_off)
    remote_control.set_command(3, ceiling_fan_high, ceiling_fan_v2_off)
    remote_control.set_command(4, stereo_on_with_cd, stereo_off)
    remote_control.set_command(5, garage_door_up, garage_door_down)

    # The same command objects sit in slots and inside the macros (shared by reference).
    party_on: list[Command] = [living_room_light_on, kitchen_light_on, ceiling_fan_on,
                               ceiling_fan_high, stereo_on_with_cd]
    party_off: list[Command] = [living_room_light_off, kitchen_light_off, ceiling_fan_off,
                                ceiling_fan_v2_off, stereo_off]
    party_on_macro = MacroCommand(party_on)
    party_off_macro = MacroCommand(party_off)

    remote_control.set_command(6, party_on_macro, party_off_macro)

    print(remote_control)

    print("\n--- Individual slots ---")
    remote_control.on_button_was_pushed(0)
    remote_control.off_button_was_pushed(0)
    remote_control.on_button_was_pushed(2)
    remote_control.off_button_was_pushed(2)
    remote_control.on_button_was_pushed(3)
    remote_control.off_button_was_pushed(3)

    print("\n--- Party mode ON (slot 6) ---")
    remote_control.on_button_was_pushed(6)

    print("\n--- Party mode OFF (slot 6) ---")
    remote_control.off_button_was_pushed(6)

    print("\n--- Undo party off ---")
    remote_control.undo_button_was_pushed()


if __name__ == "__main__":
    main()
