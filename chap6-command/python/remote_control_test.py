"""Client demo: SimpleRemoteControl (one slot) driving a light and a garage door."""
from commands import GarageDoorOpenCommand, LightOnCommand
from devices import GarageDoor, Light
from simple_remote_control import SimpleRemoteControl


def main() -> None:
    remote = SimpleRemoteControl()
    light = Light()
    light_on = LightOnCommand(light)
    remote.set_command(light_on)
    remote.button_was_pressed()
    remote.undo_button_was_pressed()

    garage_door = GarageDoor()
    garage_door_open = GarageDoorOpenCommand(garage_door)
    remote.set_command(garage_door_open)
    remote.button_was_pressed()
    remote.undo_button_was_pressed()


if __name__ == "__main__":
    main()
