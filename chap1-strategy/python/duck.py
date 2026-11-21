"""Duck (Context) and its subclasses MallardDuck and ModelDuck.

Duck composes FlyBehavior/QuackBehavior strategies instead of inheriting behavior.
"""
from abc import ABC, abstractmethod

from fly_behavior import FlyBehavior, FlyNoWay, FlyWithWings
from quack_behavior import QuackBehavior, Quack


class Duck(ABC):
    """Context: holds (has-a) a fly and a quack strategy and delegates to them."""

    def __init__(self) -> None:
        # Default strategies, as in the Java base constructor.
        self.fly_behavior: FlyBehavior = FlyWithWings()
        self.quack_behavior: QuackBehavior = Quack()

    # Varies per subclass, so it stays abstract (not a strategy).
    @abstractmethod
    def display(self) -> None: ...

    # Delegation: the duck does not fly itself, its strategy does.
    def perform_fly(self) -> None:
        self.fly_behavior.fly()

    def perform_quack(self) -> None:
        self.quack_behavior.quack()

    def swim(self) -> None:
        print("All ducks float, even decoys!")

    # Setters let behavior be swapped at runtime.
    def set_fly_behavior(self, fb: FlyBehavior) -> None:
        self.fly_behavior = fb

    def set_quack_behavior(self, qb: QuackBehavior) -> None:
        self.quack_behavior = qb


class MallardDuck(Duck):
    """Concrete context: keeps the default strategies (wings, Quack)."""

    def display(self) -> None:
        print("I'm a real Mallard duck")


class ModelDuck(Duck):
    """Concrete context: starts flightless; can be given a rocket at runtime."""

    def __init__(self) -> None:
        super().__init__()
        self.fly_behavior = FlyNoWay()
        self.quack_behavior = Quack()

    def display(self) -> None:
        print("I'm a model duck")
