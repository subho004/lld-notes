"""Server side of the remote demo: creates a GumballMachine and binds it in the
in-process Naming registry (Java: rebind with rmiregistry). Usage: <name> <inventory>.
"""
import sys
from typing import List

from gumball_machine import GumballMachine
from rmi import Naming


def main(argv: List[str] = sys.argv[1:]) -> None:
    if len(argv) < 2:
        print("GumballMachine <name> <inventory>")
        sys.exit(1)

    try:
        count = int(argv[1])
        gumball_machine = GumballMachine(argv[0], count)
        Naming.rebind("//localhost/" + argv[0], gumball_machine)
        print("Gumball machine bound at //localhost/" + argv[0])
        print(gumball_machine)
    except Exception as e:  # noqa: BLE001
        print(repr(e), file=sys.stderr)


if __name__ == "__main__":
    main()
