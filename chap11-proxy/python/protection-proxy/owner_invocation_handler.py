"""Protection-proxy handler for the person's owner: may read everything and
set all fields except the geek rating (cannot rate oneself).
"""
from typing import Any, Tuple

from invocation_handler import IllegalAccessException, InvocationHandler
from person import Person


class OwnerInvocationHandler(InvocationHandler):
    """Access-control policy for the owner; forwards allowed calls to the real Person."""
    def __init__(self, person: Person) -> None:
        self.person = person

    def invoke(self, proxy: Any, method_name: str, args: Tuple[Any, ...]) -> Any:
        # Order matters: the specific set_geek_rating rule must precede the generic set* rule.
        if method_name.startswith("get"):
            return getattr(self.person, method_name)(*args)
        elif method_name == "set_geek_rating":
            raise IllegalAccessException()
        elif method_name.startswith("set"):
            return getattr(self.person, method_name)(*args)
        return None
