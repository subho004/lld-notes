"""DuckCall: a non-Duck Context showing strategies are reusable on their own."""
from quack_behavior import Quack, QuackBehavior


class DuckCall:
    """Context that reuses QuackBehavior without being a Duck."""

    def __init__(self) -> None:
        self.quack_behavior: QuackBehavior = Quack()

    def perform_quack(self) -> None:
        self.quack_behavior.quack()

    def set_quack_behavior(self, qb: QuackBehavior) -> None:
        self.quack_behavior = qb
