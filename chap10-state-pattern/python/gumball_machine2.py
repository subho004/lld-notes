"""GumballMachine2: the Context of the State pattern, holding and switching State objects."""

from typing import Optional

from random_source import RandomSource, default_random_source
from state import (HasQuarterState, NoQuarterState, SoldOutState, SoldState,
                   State, WinnerState)


class GumballMachine2:
    """Context of the State pattern: delegates every action to the current state."""

    def __init__(self, number_gumballs: int,
                 random_source: Optional[RandomSource] = None) -> None:
        # Injected so tests are deterministic; Java instead builds a time-seeded Random inline.
        if random_source is None:
            random_source = default_random_source()
        # The context creates and owns one instance of every state; states get a back reference to us.
        self.sold_out_state: State = SoldOutState(self)
        self.no_quarter_state: State = NoQuarterState(self)
        self.has_quarter_state: State = HasQuarterState(self, random_source)
        self.sold_state: State = SoldState(self)
        self.winner_state: State = WinnerState(self)
        self.count = number_gumballs
        if number_gumballs > 0:
            self.state: State = self.no_quarter_state
        else:
            self.state = self.sold_out_state

    def insert_quarter(self) -> None:
        self.state.insert_quarter()

    def eject_quarter(self) -> None:
        self.state.eject_quarter()

    # Dispense is not user-triggered, so the context calls it right after turn_crank.
    def turn_crank(self) -> None:
        self.state.turn_crank()
        self.state.dispense()

    def refill(self, count: int) -> None:
        self.count += count
        print(f"The gumball machine was just refilled; its new count is: {self.count}")
        self.state.refill()

    # Called back by states to perform a state transition.
    def set_state(self, state: State) -> None:
        self.state = state

    # Helper used by states that dispense; it does not change state itself.
    def release_ball(self) -> None:
        print("A gumball comes rolling out the slot...")
        if self.count > 0:
            self.count -= 1

    # Getters let a state pick its successor without knowing how states are stored.
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

    def get_count(self) -> int:
        return self.count

    # `{self.state}` uses State.__str__, which mimics Java's Name@hash default.
    def __str__(self) -> str:
        result = "\nMighty Gumball, Inc."
        result += "\nJava-enabled Standing Gumball Model #2004"
        result += f"\nInventory: {self.count} gumball"
        if self.count != 1:
            result += "s"
        result += f"\nMachine is {self.state}\n"
        return result
