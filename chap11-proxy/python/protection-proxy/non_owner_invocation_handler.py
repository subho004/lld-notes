"""Protection-proxy handler for other users: may read everything and may only
set the geek rating (rate someone else), not their other fields.
"""
from typing import Any, Tuple

from invocation_handler import IllegalAccessException, InvocationHandler
from person import Person


class NonOwnerInvocationHandler(InvocationHandler):
    """Access-control policy for non-owners; forwards allowed calls to the real Person."""
    def __init__(self, person: Person) -> None:
        self.person = person

    def invoke(self, proxy: Any, method_name: str, args: Tuple[Any, ...]) -> Any:
        # Order matters: the specific set_geek_rating rule must precede the generic set* rule.
        if method_name.startswith("get"):
            return getattr(self.person, method_name)(*args)
        elif method_name == "set_geek_rating":
            return getattr(self.person, method_name)(*args)
        elif method_name.startswith("set"):
            raise IllegalAccessException()
        return None
