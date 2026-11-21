"""Tiny in-process stand-in for java.rmi (Remote, RemoteException, Naming).

There is no network: Naming.lookup hands back a stub (the *remote proxy*)
that forwards every call to the bound object, the way an RMI stub would.
"""
from __future__ import annotations

from abc import ABC
from typing import Dict


class RemoteException(Exception):
    """Checked-exception stand-in for java.rmi.RemoteException."""

    pass


class Remote(ABC):
    """Marker interface (java.rmi.Remote)."""


class Naming:
    """In-process registry replacing rmiregistry (class-level dict, no network)."""

    _registry: Dict[str, Remote] = {}

    @staticmethod
    def rebind(name: str, obj: Remote) -> None:
        Naming._registry[name] = obj

    @staticmethod
    def lookup(name: str) -> Remote:
        obj = Naming._registry.get(name)
        if obj is None:
            raise RemoteException("NotBoundException: " + name)
        # Hand out a stub, not the object itself, so callers go through the proxy.
        return obj.make_stub()  # type: ignore[attr-defined]
