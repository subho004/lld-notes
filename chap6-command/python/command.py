"""The Command interface plus the generic commands (NoCommand, LambdaCommand, MacroCommand)."""
from abc import ABC, abstractmethod
from typing import Callable, Sequence


class Command(ABC):
    """Command interface: every request is an object with execute() and undo()."""

    @abstractmethod
    def execute(self) -> None: ...

    @abstractmethod
    def undo(self) -> None: ...


class NoCommand(Command):
    """Null object: does nothing."""

    def execute(self) -> None:
        pass

    def undo(self) -> None:
        pass


class LambdaCommand(Command):
    """Generic command built from two callables, avoiding one class per action."""

    def __init__(self, execute_action: Callable[[], None], undo_action: Callable[[], None]) -> None:
        self.execute_action = execute_action
        self.undo_action = undo_action

    def execute(self) -> None:
        self.execute_action()

    def undo(self) -> None:
        self.undo_action()


class MacroCommand(Command):
    """Composite-like command: runs a list of commands in order, undoes them in reverse."""

    def __init__(self, commands: Sequence[Command]) -> None:
        self.commands = list(commands)

    def execute(self) -> None:
        for command in self.commands:
            command.execute()

    def undo(self) -> None:
        # Reverse order so later effects are undone first.
        for command in reversed(self.commands):
            command.undo()
