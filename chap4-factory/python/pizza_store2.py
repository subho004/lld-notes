"""Factory Method + Abstract Factory: PizzaStore2 and its regional stores."""
from abc import ABC, abstractmethod
from typing import Optional

from ingredient_factory import (
    ChicagoPizzaIngredientFactory, IngredientFactory, NYPizzaIngredientFactory,
)
from pizza2 import CheesePizza2, ClamPizza2, PepperoniPizza2, Pizza2, VeggiePizza2


# Creator again, but products are built with a regional IngredientFactory
# (Abstract Factory) instead of hard-coded ingredient strings.
class PizzaStore2(ABC):
    def order_pizza(self, type: str) -> Pizza2:
        pizza = self.create_pizza(type)
        pizza.prepare()
        pizza.bake()
        pizza.cut()
        pizza.box()
        return pizza

    @abstractmethod
    def create_pizza(self, type: str) -> Pizza2: ...


# Python-only: the Java regional stores repeat this if/else chain; it is factored
# into one helper here. Names and flow match Java (e.g. 'New York Style Cheese Pizza').
def _create(factory: IngredientFactory, region: str, item: str) -> Optional[Pizza2]:
    pizza: Optional[Pizza2] = None
    if item == "cheese":
        pizza = CheesePizza2(factory)
        pizza.set_name(region + " Style Cheese Pizza")
    elif item == "veggie":
        pizza = VeggiePizza2(factory)
        pizza.set_name(region + " Style Veggie Pizza")
    elif item == "pepperoni":
        pizza = PepperoniPizza2(factory)
        pizza.set_name(region + " Style Pepperoni Pizza")
    elif item == "clam":
        pizza = ClamPizza2(factory)
        pizza.set_name(region + " Style Clam Pizza")
    return pizza


# Concrete Creator: injects the NY ingredient factory into every pizza.
class NYPizzaStore2(PizzaStore2):
    def create_pizza(self, item: str) -> Pizza2:
        return _create(NYPizzaIngredientFactory(), "New York", item)


# Concrete Creator: injects the Chicago ingredient factory into every pizza.
class ChicagoPizzaStore2(PizzaStore2):
    def create_pizza(self, item: str) -> Pizza2:
        return _create(ChicagoPizzaIngredientFactory(), "Chicago", item)
