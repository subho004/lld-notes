"""Component side of the Decorator pattern: abstract Beverage and the four concrete coffees."""

from abc import ABC, abstractmethod

from size import Size


class Beverage(ABC):
    """Component: the common interface for plain coffees and condiment decorators."""

    def __init__(self) -> None:
        self.description: str = "Unknown Beverage"
        self.size: Size = Size.TALL

    def get_size(self) -> Size:
        return self.size

    def set_size(self, size: Size) -> None:
        self.size = size

    def cost(self) -> float:
        # Base cost covers only built-in condiment flags; concrete coffees add their own price.
        condiment_cost = 0.0
        if self.has_milk():
            condiment_cost += 0.10
        if self.has_soy():
            condiment_cost += 0.15
        if self.has_mocha():
            condiment_cost += 0.20
        if self.has_whip():
            condiment_cost += 0.25
        return condiment_cost

    # Abstract (via ABC) so every subclass must declare its built-in condiments.
    @abstractmethod
    def has_milk(self) -> bool: ...

    @abstractmethod
    def has_soy(self) -> bool: ...

    @abstractmethod
    def has_mocha(self) -> bool: ...

    @abstractmethod
    def has_whip(self) -> bool: ...

    def get_description(self) -> str:
        return f"{self.size} {self.description}"


class _NoCondiments(Beverage):
    """Helper for the concrete coffees: they have no built-in condiment flags."""

    def has_milk(self) -> bool:
        return False

    def has_soy(self) -> bool:
        return False

    def has_mocha(self) -> bool:
        return False

    def has_whip(self) -> bool:
        return False


class DarkRoast(_NoCondiments):
    """Concrete Component."""

    def __init__(self) -> None:
        super().__init__()
        self.description = "Dark Roast Coffee"

    def cost(self) -> float:
        return 0.99 + super().cost()


class Decaf(_NoCondiments):
    """Concrete Component."""

    def __init__(self) -> None:
        super().__init__()
        self.description = "Decaf Coffee"

    def cost(self) -> float:
        return 1.05 + super().cost()


class Expresso(_NoCondiments):
    """Concrete Component."""

    def __init__(self) -> None:
        super().__init__()
        self.description = "Expresso"

    def cost(self) -> float:
        return 1.99 + super().cost()


class HouseBlend(_NoCondiments):
    """Concrete Component."""

    def __init__(self) -> None:
        super().__init__()
        self.description = "House Blend Coffee"

    def cost(self) -> float:
        return 0.89 + super().cost()
