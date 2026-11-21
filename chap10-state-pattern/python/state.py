"""State interface plus the five Concrete States (NoQuarter, HasQuarter, Sold, SoldOut, Winner)."""

from __future__ import annotations

from abc import ABC, abstractmethod
from typing import TYPE_CHECKING

if TYPE_CHECKING:  # avoids a circular import with gumball_machine2
    from gumball_machine2 import GumballMachine2


# State interface: ABC + @abstractmethod replaces Java's `interface State`.
class State(ABC):
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

    def __str__(self) -> str:
        # Mimics Java's default Object.toString(): ClassName@hex
        return f"{type(self).__name__}@{id(self) & 0xFFFFFFFF:x}"


# Concrete State: machine has gumballs but no quarter is inserted.
class NoQuarterState(State):
    def __init__(self, gumball_machine: GumballMachine2) -> None:
        self.gumball_machine = gumball_machine

    def insert_quarter(self) -> None:
        print("You inserted a quarter")
        self.gumball_machine.set_state(self.gumball_machine.get_has_quarter_state())

    def eject_quarter(self) -> None:
        print("You haven't inserted a quarter")

    def turn_crank(self) -> None:
        print("You turned, but there's no quarter")

    def dispense(self) -> None:
        print("You need to pay first")

    def refill(self) -> None:
        pass


# Concrete State: quarter inserted; turning the crank may pick the winner path.
class HasQuarterState(State):
    def __init__(self, gumball_machine: GumballMachine2, random_winner) -> None:
        self.gumball_machine = gumball_machine
        self.random_winner = random_winner  # RandomSource, injected

    def insert_quarter(self) -> None:
        print("You can't insert another quarter")

    def eject_quarter(self) -> None:
        print("Quarter returned")
        self.gumball_machine.set_state(self.gumball_machine.get_no_quarter_state())

    def turn_crank(self) -> None:
        print("You turned...")
        # 0 means winner, but only if at least 2 balls remain to give out.
        winner = self.random_winner.next_int(10)
        if winner == 0 and self.gumball_machine.get_count() > 1:
            self.gumball_machine.set_state(self.gumball_machine.get_winner_state())
        else:
            self.gumball_machine.set_state(self.gumball_machine.get_sold_state())

    def dispense(self) -> None:
        print("No gumball dispensed")

    def refill(self) -> None:
        pass


# Concrete State: crank turned; dispense() releases one ball and picks the next state.
class SoldState(State):
    def __init__(self, gumball_machine: GumballMachine2) -> None:
        self.gumball_machine = gumball_machine

    def insert_quarter(self) -> None:
        print("Please wait, we're already giving you a gumball")

    def eject_quarter(self) -> None:
        print("Sorry, you already turned the crank")

    def turn_crank(self) -> None:
        print("Turning twice doesn't get you another gumball!")

    def dispense(self) -> None:
        self.gumball_machine.release_ball()
        if self.gumball_machine.get_count() > 0:
            self.gumball_machine.set_state(self.gumball_machine.get_no_quarter_state())
        else:
            print("Oops, out of gumballs!")
            self.gumball_machine.set_state(self.gumball_machine.get_sold_out_state())

    def refill(self) -> None:
        pass


# Concrete State: no gumballs left; only refill() leaves this state.
class SoldOutState(State):
    def __init__(self, gumball_machine: GumballMachine2) -> None:
        self.gumball_machine = gumball_machine

    def insert_quarter(self) -> None:
        print("You can't insert a quarter, the machine is sold out")

    def eject_quarter(self) -> None:
        print("You can't eject, you haven't inserted a quarter yet")

    def turn_crank(self) -> None:
        print("You turned, but there are no gumballs")

    def dispense(self) -> None:
        print("No gumball dispensed")

    def refill(self) -> None:
        self.gumball_machine.set_state(self.gumball_machine.get_no_quarter_state())


# Concrete State: 1-in-10 winner, dispenses two gumballs for one quarter.
class WinnerState(State):
    def __init__(self, gumball_machine: GumballMachine2) -> None:
        self.gumball_machine = gumball_machine

    def insert_quarter(self) -> None:
        print("Please wait, we're already giving you a gumball")

    def eject_quarter(self) -> None:
        print("Sorry, you already turned the crank")

    def turn_crank(self) -> None:
        print("Turning twice doesn't get you another gumball!")

    def dispense(self) -> None:
        print("YOU'RE A WINNER! You get two gumballs for your quarter")
        # Releases the first ball; a second one follows only if stock remains.
        self.gumball_machine.release_ball()
        if self.gumball_machine.get_count() == 0:
            self.gumball_machine.set_state(self.gumball_machine.get_sold_out_state())
        else:
            self.gumball_machine.release_ball()
            if self.gumball_machine.get_count() > 0:
                self.gumball_machine.set_state(self.gumball_machine.get_no_quarter_state())
            else:
                print("Oops, out of gumballs!")
                self.gumball_machine.set_state(self.gumball_machine.get_sold_out_state())

    def refill(self) -> None:
        pass
