"""Abstract Factory: IngredientFactory and the regional factories."""
from abc import ABC, abstractmethod
from typing import List

from ingredients import (
    BlackOlives, Cheese, Clams, Dough, Eggplant, FreshClams, FrozenClams,
    Garlic, MarinaraSauce, MozzarellaCheese, Mushroom, Onion, Pepperoni,
    PlumTomatoSauce, RedPepper, ReggianoCheese, Sauce, SlicedPepperoni,
    Spinach, ThickCrustDough, ThinCrustDough, Veggies,
)


# Abstract Factory: one create_* method per ingredient in a pizza family.
# ABC + @abstractmethod forbids instantiating it or a half-implemented factory.
class IngredientFactory(ABC):
    @abstractmethod
    def create_dough(self) -> Dough: ...

    @abstractmethod
    def create_sauce(self) -> Sauce: ...

    @abstractmethod
    def create_cheese(self) -> Cheese: ...

    @abstractmethod
    def create_veggies(self) -> List[Veggies]: ...

    @abstractmethod
    def create_pepperoni(self) -> Pepperoni: ...

    @abstractmethod
    def create_clam(self) -> Clams: ...


# Concrete Factory: produces the Chicago family (thick crust, plum tomato, mozzarella).
class ChicagoPizzaIngredientFactory(IngredientFactory):
    def create_dough(self) -> Dough:
        return ThickCrustDough()

    def create_sauce(self) -> Sauce:
        return PlumTomatoSauce()

    def create_cheese(self) -> Cheese:
        return MozzarellaCheese()

    # Each call builds a fresh list, so pizzas never share ingredient objects.
    def create_veggies(self) -> List[Veggies]:
        return [Spinach(), Eggplant(), BlackOlives()]

    def create_pepperoni(self) -> Pepperoni:
        return SlicedPepperoni()

    def create_clam(self) -> Clams:
        return FrozenClams()


# Concrete Factory: produces the New York family (thin crust, marinara, reggiano).
class NYPizzaIngredientFactory(IngredientFactory):
    def create_dough(self) -> Dough:
        return ThinCrustDough()

    def create_sauce(self) -> Sauce:
        return MarinaraSauce()

    def create_cheese(self) -> Cheese:
        return ReggianoCheese()

    def create_veggies(self) -> List[Veggies]:
        return [Garlic(), Onion(), Mushroom(), RedPepper()]

    def create_pepperoni(self) -> Pepperoni:
        return SlicedPepperoni()

    def create_clam(self) -> Clams:
        return FreshClams()
