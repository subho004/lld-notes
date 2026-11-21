"""GumballMachineStub (Remote Proxy) and GumballMachine (Real Subject and
State-pattern Context).
"""
from __future__ import annotations

from gumball_machine_remote import GumballMachineRemote
from state import State
from states import (HasQuarterState, NoQuarterState, SoldOutState, SoldState,
                    WinnerState)


class GumballMachineStub(GumballMachineRemote):
    """Remote proxy: what Naming.lookup returns instead of the real machine."""

    def __init__(self, target: GumballMachineRemote) -> None:
        self._target = target

    def get_count(self) -> int:
        return self._target.get_count()

    def get_location(self) -> str:
        return self._target.get_location()

    def get_state(self) -> State:
        return self._target.get_state()


class GumballMachine(GumballMachineRemote):
    """Real Subject and State Context: owns the state objects and delegates to one."""

    def __init__(self, location: str, number_gumballs: int) -> None:
    # Each state gets a back-reference so it can call set_state() on the machine.
        self.sold_out_state: State = SoldOutState(self)
        self.no_quarter_state: State = NoQuarterState(self)
        self.has_quarter_state: State = HasQuarterState(self)
        self.sold_state: State = SoldState(self)
        self.winner_state: State = WinnerState(self)
        self.count = number_gumballs
        self.location = location
        self.state: State = self.no_quarter_state if number_gumballs > 0 else self.sold_out_state

    # Called by Naming.lookup (see rmi.py); simulates RMI exporting the object.
    def make_stub(self) -> GumballMachineRemote:
        return GumballMachineStub(self)

    def insert_quarter(self) -> None:
        self.state.insert_quarter()

    def eject_quarter(self) -> None:
        self.state.eject_quarter()

    def turn_crank(self) -> None:
    # Delegation to the current State; dispense() runs after the state change.
        self.state.turn_crank()
        self.state.dispense()

    def refill(self, count: int) -> None:
        self.count += count
        print("The gumball machine was just refilled; its new count is: " + str(self.count))
        self.state.refill()

    def set_state(self, state: State) -> None:
        self.state = state

    def release_ball(self) -> None:
        print("A gumball comes rolling out the slot...")
        if self.count > 0:
            self.count -= 1

    def get_location(self) -> str:
        return self.location

    def get_count(self) -> int:
        return self.count

    def get_state(self) -> State:
        return self.state

    def get_sold_out_state(self) -> State:
        return self.sold_out_state

    def get_no_quarter_state(self) -> State:
        return self.no_quarter_state

    def get_has_quarter_state(self) -> State:
        return self.has_quarter_state

    def get_sold_state(self) -> State:
        return self.sold_state

    def get_winner_state(self) -> State:
        return self.winner_state

    def __str__(self) -> str:
        result = "\nMighty Gumball, Inc."
        result += "\nJava-enabled Standing Gumball Model #2004"
        result += "\nInventory: " + str(self.count) + " gumball"
        if self.count != 1:
            result += "s"
        result += "\nMachine is " + str(self.state) + "\n"
        return result
