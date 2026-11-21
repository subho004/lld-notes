"""Invoker with 7 on/off slots; knows only the Command interface, never the receivers."""
from typing import List

from command import Command, NoCommand


class RemoteControl:
    """Invoker with 7 on/off slots and a one-level undo."""

    def __init__(self) -> None:
        # Null object: every slot starts with a safe do-nothing command, so no None checks.
        no_command: Command = NoCommand()
        self.undo_command: Command = no_command
        self.on_commands: List[Command] = [no_command] * 7
        self.off_commands: List[Command] = [no_command] * 7

    def set_command(self, slot: int, on_command: Command, off_command: Command) -> None:
        self.on_commands[slot] = on_command
        self.off_commands[slot] = off_command

    def on_button_was_pushed(self, slot: int) -> None:
        # Remember the last command so undo can reverse it.
        self.undo_command = self.on_commands[slot]
        self.on_commands[slot].execute()

    def off_button_was_pushed(self, slot: int) -> None:
        self.undo_command = self.off_commands[slot]
        self.off_commands[slot].execute()

    def undo_button_was_pushed(self) -> None:
        self.undo_command.undo()

    def __str__(self) -> str:
        # type(x).__name__ plays the role of Java's getClass().getName().
        out = "\n------ Remote Control ------\n"
        for i, (on, off) in enumerate(zip(self.on_commands, self.off_commands)):
            out += "[slot %d] %s    %s\n" % (i, type(on).__name__, type(off).__name__)
        return out
