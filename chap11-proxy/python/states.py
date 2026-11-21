"""Concrete State classes (NoQuarter, HasQuarter, Sold, Winner, SoldOut).

Each state implements the machine's behaviour for that moment and moves
the machine to the next state through set_state().
"""
from __future__ import annotations

import random
from typing import TYPE_CHECKING

from state import State

# Imported only for type checking: gumball_machine imports this module, so a
# runtime import would be circular.
if TYPE_CHECKING:
    from gumball_machine import GumballMachine


class NoQuarterState(State):
    """Concrete State: idle, waiting for a quarter."""
    def __init__(self, gumball_machine: GumballMachine) -> None:
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

    def __str__(self) -> str:
        return "waiting for quarter"


class HasQuarterState(State):
    """Concrete State: quarter inserted; the crank may be turned (or quarter ejected)."""
    def __init__(self, gumball_machine: GumballMachine) -> None:
        self.gumball_machine = gumball_machine
        # Java seeds with currentTimeMillis(); fixed seed keeps runs repeatable.
        self.random_winner = random.Random(42)

    def insert_quarter(self) -> None:
        print("You can't insert another quarter")

    def eject_quarter(self) -> None:
        print("Quarter returned")
        self.gumball_machine.set_state(self.gumball_machine.get_no_quarter_state())

    def turn_crank(self) -> None:
        print("You turned...")
        # State transition: a winner needs at least 2 gumballs left to pay out.
        winner = self.random_winner.randrange(10)
        if winner == 0 and self.gumball_machine.get_count() > 1:
            self.gumball_machine.set_state(self.gumball_machine.get_winner_state())
        else:
            self.gumball_machine.set_state(self.gumball_machine.get_sold_state())

    def dispense(self) -> None:
        print("No gumball dispensed")

    def refill(self) -> None:
        pass

    def __str__(self) -> str:
        return "waiting for turn of crank"


class SoldState(State):
    """Concrete State: crank turned, dispensing one gumball."""
    def __init__(self, gumball_machine: GumballMachine) -> None:
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

    def __str__(self) -> str:
        return "dispensing a gumball"


class WinnerState(State):
    """Concrete State: lucky draw (about 1 in 10), dispensing two gumballs."""
    def __init__(self, gumball_machine: GumballMachine) -> None:
        self.gumball_machine = gumball_machine

    def insert_quarter(self) -> None:
        print("Please wait, we're already giving you a gumball")

    def eject_quarter(self) -> None:
        print("Sorry, you already turned the crank")

    def turn_crank(self) -> None:
        print("Turning twice doesn't get you another gumball!")

    def dispense(self) -> None:
        print("YOU'RE A WINNER! You get two gumballs for your quarter")
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

    def __str__(self) -> str:
        return "dispensing two gumballs for your quarter, because YOU'RE A WINNER!"


class SoldOutState(State):
    """Concrete State: no gumballs left; only refill() leaves this state."""
    def __init__(self, gumball_machine: GumballMachine) -> None:
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

    def __str__(self) -> str:
        return "sold out"
