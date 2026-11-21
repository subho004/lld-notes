"""Test drive (client) for GumballMachine2, the State-pattern version."""

from gumball_machine2 import GumballMachine2


# Client: drives the State-pattern machine; callers never see the State objects.
def main() -> None:
    gumball_machine = GumballMachine2(5)
    print(gumball_machine)

    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    print(gumball_machine)

    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    print(gumball_machine)

    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    print(gumball_machine)

    print("--- Refilling ---")
    gumball_machine.refill(5)
    print(gumball_machine)

    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    print(gumball_machine)


if __name__ == "__main__":
    main()
