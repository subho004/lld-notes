"""Subject interface of the remote proxy.

Both the real GumballMachine and its stub implement it, so GumballMonitor
cannot tell which one it holds.
"""
from abc import abstractmethod

from rmi import Remote
from state import State


class GumballMachineRemote(Remote):
    """Subject: the remote-callable view of a gumball machine."""
    @abstractmethod
    def get_count(self) -> int: ...

    @abstractmethod
    def get_location(self) -> str: ...

    @abstractmethod
    def get_state(self) -> State: ...
