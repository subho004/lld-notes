"""Ingredient interfaces and concrete ingredients (Abstract Factory products)."""
from abc import ABC


# Product interfaces of the Abstract Factory. They are empty marker ABCs;
# printing relies on each concrete ingredient's __str__ (Java used toString()).
class Dough(ABC):
    pass


class Sauce(ABC):
    pass


class Cheese(ABC):
    pass


class Veggies(ABC):
    pass


class Pepperoni(ABC):
    pass


class Clams(ABC):
    pass


# Concrete products: one class per regional ingredient, differing only in text.
class ThickCrustDough(Dough):
    def __str__(self) -> str:
        return "Thick Crust Dough"


class ThinCrustDough(Dough):
    def __str__(self) -> str:
        return "Thin Crust Dough"


class MarinaraSauce(Sauce):
    def __str__(self) -> str:
        return "Marinara Sauce"


class PlumTomatoSauce(Sauce):
    def __str__(self) -> str:
        return "Plum Tomato Sauce"


class MozzarellaCheese(Cheese):
    def __str__(self) -> str:
        return "Mozzarella Cheese"


class ReggianoCheese(Cheese):
    def __str__(self) -> str:
        return "Reggiano Cheese"


class BlackOlives(Veggies):
    def __str__(self) -> str:
        return "Black Olives"


class Eggplant(Veggies):
    def __str__(self) -> str:
        return "Eggplant"


class Garlic(Veggies):
    def __str__(self) -> str:
        return "Garlic"


class Mushroom(Veggies):
    def __str__(self) -> str:
        return "Mushroom"


class Onion(Veggies):
    def __str__(self) -> str:
        return "Onion"


class RedPepper(Veggies):
    def __str__(self) -> str:
        return "Red Pepper"


class Spinach(Veggies):
    def __str__(self) -> str:
        return "Spinach"


class SlicedPepperoni(Pepperoni):
    def __str__(self) -> str:
        return "Sliced Pepperoni"


class FreshClams(Clams):
    def __str__(self) -> str:
        return "Fresh Clams"


class FrozenClams(Clams):
    def __str__(self) -> str:
        return "Frozen Clams"
