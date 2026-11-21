"""Factory Method: PizzaStore and its regional subclasses."""
from abc import ABC, abstractmethod

from pizza import (
    CaliforniaStyleCheesePizza, CaliforniaStyleClamPizza,
    CaliforniaStylePepperoniPizza, CaliforniaStyleVeggiePizza,
    NYStyleCheesePizza, NYStyleClamPizza, NYStylePepperoniPizza,
    NYStyleVeggiePizza, Pizza,
)


# Creator in the Factory Method pattern: order_pizza() is the fixed workflow and
# defers the choice of concrete Pizza to the create_pizza() subclass hook.
class PizzaStore(ABC):
    def order_pizza(self, type: str) -> Pizza:
        pizza = self.create_pizza(type)
        pizza.prepare()
        pizza.bake()
        pizza.cut()
        pizza.box()
        return pizza

    @abstractmethod
    # The factory method; returns None for an unknown type (as Java returned null).
    def create_pizza(self, type: str) -> Pizza: ...


# Concrete Creator: decides which NY-style product to instantiate.
class NYStylePizzaStore(PizzaStore):
    def create_pizza(self, type: str) -> Pizza:
        pizza = None
        if type == "cheese":
            pizza = NYStyleCheesePizza()
        elif type == "pepperoni":
            pizza = NYStylePepperoniPizza()
        elif type == "clam":
            pizza = NYStyleClamPizza()
        elif type == "veggie":
            pizza = NYStyleVeggiePizza()
        return pizza


# Concrete Creator: decides which California-style product to instantiate.
class CaliforniaStylePizzaStore(PizzaStore):
    def create_pizza(self, type: str) -> Pizza:
        pizza = None
        if type == "cheese":
            pizza = CaliforniaStyleCheesePizza()
        elif type == "pepperoni":
            pizza = CaliforniaStylePepperoniPizza()
        elif type == "clam":
            pizza = CaliforniaStyleClamPizza()
        elif type == "veggie":
            pizza = CaliforniaStyleVeggiePizza()
        return pizza
