"""Client side of the remote demo: looks machines up by name (receiving stubs)
and reports on them through GumballMonitor.
"""
import sys
from typing import List, Optional

from gumball_machine import GumballMachine
from gumball_machine_remote import GumballMachineRemote
from gumball_monitor import GumballMonitor
from rmi import Naming


def bind_demo_machines() -> None:
    """Simulation only: the Java version relies on separately started
    GumballMachineTestDrive JVMs registered with rmiregistry."""
    Naming.rebind("//localhost/santafe", GumballMachine("santafe", 112))
    Naming.rebind("//localhost/boulder", GumballMachine("boulder", 0))
    Naming.rebind("//localhost/seattle", GumballMachine("seattle", 1))


def main(argv: List[str] = sys.argv[1:]) -> None:
    locations = ["santafe", "boulder", "seattle"]
    if len(argv) > 0:
        locations = argv

    bind_demo_machines()
    monitors: List[Optional[GumballMonitor]] = [None] * len(locations)

    for i, location in enumerate(locations):
        try:
            # lookup returns a GumballMachineStub (the remote proxy), typed as the interface.
            machine: GumballMachineRemote = Naming.lookup("//localhost/" + location)  # type: ignore[assignment]
            monitors[i] = GumballMonitor(machine)
            print(monitors[i])
        except Exception as e:  # noqa: BLE001
            print(repr(e), file=sys.stderr)

    for monitor in monitors:
        if monitor is not None:
            monitor.report()
            print()


if __name__ == "__main__":
    main()
