"""GumballMonitor: the remote proxy's client.

It depends only on the GumballMachineRemote interface, so it works with a
stub or a local machine alike.
"""
import itertools
import sys

from gumball_machine_remote import GumballMachineRemote
from rmi import RemoteException


class GumballMonitor:
    # Class-wide counter standing in for Java's identity hash in __str__.
    _ids = itertools.count(1)

    def __init__(self, machine: GumballMachineRemote) -> None:
        self.machine = machine
        self._id = next(GumballMonitor._ids)

    def report(self) -> None:
        try:
            print("Gumball Machine: " + self.machine.get_location())
            print("Current inventory: " + str(self.machine.get_count()) + " gumballs")
            print("Current state: " + str(self.machine.get_state()))
        # A remote call can fail; real RMI makes this a checked exception.
        except RemoteException as e:
            print(repr(e), file=sys.stderr)

    def __str__(self) -> str:
        # Java prints GumballMonitor@<identity hash>; use a deterministic id.
        return "GumballMonitor@" + format(self._id, "x")
