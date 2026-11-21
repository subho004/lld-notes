"""TurkeyAdapter: Object Adapter that lets a Turkey be used where a Duck is expected."""
from duck import Duck
from turkey import Turkey


class TurkeyAdapter(Duck):
    """Adapts a Turkey to the Duck interface."""

    def __init__(self, turkey: Turkey) -> None:
        self.turkey = turkey

    def quack(self) -> None:
        # Translate the Duck call into the equivalent Turkey call.
        self.turkey.gobble()

    def fly(self) -> None:
        # Turkeys fly short distances, so call fly 5 times to approximate a duck flight.
        for _ in range(5):
            self.turkey.fly()
