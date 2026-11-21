"""Test drive (client) for the state-less GumballMachine."""

from gumball_machine import GumballMachine


# Client: drives the state-less v1 machine through the same scenarios as the Java TestDrive.
def main() -> None:
    gumball_machine = GumballMachine(5)
    print(gumball_machine)

    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    print(gumball_machine)

    gumball_machine.insert_quarter()
    gumball_machine.eject_quarter()
    gumball_machine.turn_crank()
    print(gumball_machine)

    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    gumball_machine.eject_quarter()
    print(gumball_machine)

    gumball_machine.insert_quarter()
    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    gumball_machine.insert_quarter()
    gumball_machine.turn_crank()
    print(gumball_machine)


if __name__ == "__main__":
    main()
