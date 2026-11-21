"""Client demo: commands built from lambdas (LambdaCommand) instead of concrete command classes."""
from command import LambdaCommand
from devices import CeilingFan, GarageDoor, Light, Stereo
from remote_control import RemoteControl


def main() -> None:
    remote_control = RemoteControl()

    living_room_light = Light("Living Room")
    kitchen_light = Light("Kitchen")
    ceiling_fan = CeilingFan("Living Room")
    garage_door = GarageDoor("Garage")
    stereo = Stereo("Living Room")

    remote_control.set_command(
        0,
        LambdaCommand(lambda: living_room_light.on(), lambda: living_room_light.off()),
        LambdaCommand(lambda: living_room_light.off(), lambda: living_room_light.on()))

    remote_control.set_command(
        1,
        LambdaCommand(lambda: kitchen_light.on(), lambda: kitchen_light.off()),
        LambdaCommand(lambda: kitchen_light.off(), lambda: kitchen_light.on()))

    remote_control.set_command(
        2,
        LambdaCommand(lambda: ceiling_fan.on(), lambda: ceiling_fan.off()),
        LambdaCommand(lambda: ceiling_fan.off(), lambda: ceiling_fan.on()))

    def stereo_on_with_cd() -> None:  # Python lambdas are single-expression, so use a def
        stereo.on()
        stereo.set_cd()
        stereo.set_volume(11)

    remote_control.set_command(
        3,
        LambdaCommand(stereo_on_with_cd, lambda: stereo.off()),
        LambdaCommand(lambda: stereo.off(), lambda: stereo.on()))

    remote_control.set_command(
        4,
        LambdaCommand(lambda: garage_door.up(), lambda: garage_door.down()),
        LambdaCommand(lambda: garage_door.down(), lambda: garage_door.up()))

    print("------ Remote Control (Lambda) ------")
    print(remote_control)

    print("\n--- Slot 0: Living Room Light ---")
    remote_control.on_button_was_pushed(0)
    remote_control.undo_button_was_pushed()

    print("\n--- Slot 3: Stereo with CD ---")
    remote_control.on_button_was_pushed(3)
    remote_control.undo_button_was_pushed()

    print("\n--- Slot 4: Garage Door ---")
    remote_control.on_button_was_pushed(4)
    remote_control.undo_button_was_pushed()


if __name__ == "__main__":
    main()
