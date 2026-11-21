"""State interface of the State pattern.

GumballMachine delegates every action to its current State. The same
method set serves all five concrete states in states.py.
"""
from abc import ABC, abstractmethod


class State(ABC):
    """Strategy-like State interface; ABC makes it impossible to instantiate."""
    @abstractmethod
    def insert_quarter(self) -> None: ...

    @abstractmethod
    def eject_quarter(self) -> None: ...

    @abstractmethod
    def turn_crank(self) -> None: ...

    @abstractmethod
    def dispense(self) -> None: ...

    @abstractmethod
    def refill(self) -> None: ...
