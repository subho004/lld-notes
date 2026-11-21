"""Python stand-in for java.lang.reflect.InvocationHandler / Proxy.

Java generates a proxy class at runtime via reflection; here __getattr__
plays that role (see _DynamicProxy). Holds the handler interface, the
access-denied exception and the proxy factory.
"""
from abc import ABC, abstractmethod
from typing import Any, Callable, Tuple, Type


class IllegalAccessException(Exception):
    """Raised by a handler when the caller may not use the method."""

    pass


class InvocationHandler(ABC):
    """Strategy for access control: decides whether and how to forward a call."""

    @abstractmethod
    def invoke(self, proxy: Any, method_name: str, args: Tuple[Any, ...]) -> Any: ...


class _DynamicProxy:
    """Every attribute lookup yields a closure that forwards to the handler,
    so the proxy needs no hand-written method per interface method."""

    def __init__(self, interface: Type, handler: InvocationHandler) -> None:
        self._interface = interface
        self._handler = handler

    def __getattr__(self, name: str) -> Callable[..., Any]:
        # Only names declared on the interface are proxied; dunder/private lookups
        # fall through so normal Python machinery keeps working.
        if name.startswith("_") or not hasattr(self._interface, name):
            raise AttributeError(name)

        def call(*args: Any) -> Any:
            # Forwarding point: all access control happens in the handler.
            return self._handler.invoke(self, name, args)

        return call


def new_proxy_instance(interface: Type, handler: InvocationHandler) -> Any:
    """Like Proxy.newProxyInstance(loader, interfaces, handler)."""
    return _DynamicProxy(interface, handler)
