"""GumballMachine (v1): the "before" design, with an int state and if/else in every method."""


class GumballMachine:
    """First, state-less design: every action is an if/else over an int state."""

    # Int constants stand in for Java's `static final int`; each is a state id.
    SOLD_OUT = 0
    NO_QUARTER = 1
    HAS_QUARTER = 2
    SOLD = 3

    def __init__(self, count: int) -> None:
        self.state = GumballMachine.SOLD_OUT
        self.count = count
        if count > 0:
            self.state = GumballMachine.NO_QUARTER

    def insert_quarter(self) -> None:
        if self.state == self.HAS_QUARTER:
            print("You can't insert another quarter")
        elif self.state == self.NO_QUARTER:
            self.state = self.HAS_QUARTER
            print("You inserted a quarter")
        elif self.state == self.SOLD_OUT:
            print("You can't insert a quarter, the machine is sold out")
        elif self.state == self.SOLD:
            print("Please wait, we're already giving you a gumball")

    def eject_quarter(self) -> None:
        if self.state == self.HAS_QUARTER:
            print("Quarter returned")
            self.state = self.NO_QUARTER
        elif self.state == self.NO_QUARTER:
            print("You haven't inserted a quarter")
        elif self.state == self.SOLD_OUT:
            print("You can't eject, you haven't inserted a quarter yet")
        elif self.state == self.SOLD:
            print("Sorry, you already turned the crank")

    def turn_crank(self) -> None:
        if self.state == self.SOLD:
            print("Turning twice doesn't get you another gumball!")
        elif self.state == self.NO_QUARTER:
            print("You turned but there's no quarter")
        elif self.state == self.SOLD_OUT:
            print("You turned, but there are no gumballs")
        elif self.state == self.HAS_QUARTER:
            print("You turned...")
            self.state = self.SOLD
            self.dispense()

    # Also branches on state, which is the duplication the State pattern removes.
    def dispense(self) -> None:
        if self.state == self.SOLD:
            print("A gumball comes rolling out the slot")
            self.count -= 1
            if self.count == 0:
                print("Oops, out of gumballs!")
                self.state = self.SOLD_OUT
            else:
                self.state = self.NO_QUARTER
        elif self.state == self.NO_QUARTER:
            print("You need to pay first")
        elif self.state == self.SOLD_OUT:
            print("No gumballs dispensed")
        elif self.state == self.HAS_QUARTER:
            print("No gumball dispensed")

    # Mirrors Java's toString(); another per-state if/else chain.
    def __str__(self) -> str:
        result = "\nMighty Gumball, Inc."
        result += "\nJava-enabled Standing Gumball Model #2004"
        result += f"\nInventory: {self.count} gumball"
        if self.count != 1:
            result += "s"
        result += "\n"
        if self.state == self.SOLD_OUT:
            result += "Machine is sold out"
        elif self.state == self.NO_QUARTER:
            result += "Machine is waiting for quarter"
        elif self.state == self.HAS_QUARTER:
            result += "Machine is waiting for turn of crank"
        elif self.state == self.SOLD:
            result += "Gumball is on its way!"
        result += "\n"
        return result
