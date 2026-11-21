"""DuckAdapter: Object Adapter that lets a Duck be used where a Turkey is expected."""
from duck import Duck
from turkey import Turkey


class DuckAdapter(Turkey):
    """Adapts a Duck to the Turkey interface."""

    def __init__(self, duck: Duck) -> None:
        self.duck = duck

    def gobble(self) -> None:
        # Translate the Turkey call into the equivalent Duck call.
        self.duck.quack()

    def fly(self) -> None:
        # A turkey flies only a short distance, so a duck flies 5 times to match.
        for _ in range(5):
            self.duck.fly()
