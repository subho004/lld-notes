"""Abstract Factory version of Pizza: Pizza2 and the ingredient-driven pizzas."""
from abc import ABC, abstractmethod
from typing import List, Optional

from ingredient_factory import IngredientFactory
from ingredients import Cheese, Clams, Dough, Pepperoni, Sauce, Veggies


# Abstract product. Ingredients start as None and are only created in prepare(),
# by asking the IngredientFactory; ingredient fields stay Optional until then.
class Pizza2(ABC):
    def __init__(self) -> None:
        self.name: str = ""
        self.dough: Optional[Dough] = None
        self.sauce: Optional[Sauce] = None
        self.veggies: Optional[List[Veggies]] = None
        self.cheese: Optional[Cheese] = None
        self.pepperoni: Optional[Pepperoni] = None
        self.clams: Optional[Clams] = None

    @abstractmethod
    def prepare(self) -> None: ...

    def bake(self) -> None:
        print("Bake for 25 minutes at 350")

    def cut(self) -> None:
        print("Cutting the pizza into diagonal slices")

    def box(self) -> None:
        print("Place pizza in official PizzaStore box")

    def set_name(self, name: str) -> None:
        self.name = name

    def get_name(self) -> str:
        return self.name

    # Prints only the ingredients that were actually created.
    def __str__(self) -> str:
        result = "---- " + self.name + " ----\n"
        if self.dough is not None:
            result += str(self.dough) + "\n"
        if self.sauce is not None:
            result += str(self.sauce) + "\n"
        if self.cheese is not None:
            result += str(self.cheese) + "\n"
        if self.veggies is not None:
            result += ", ".join(str(v) for v in self.veggies) + "\n"
        if self.pepperoni is not None:
            result += str(self.pepperoni) + "\n"
        if self.clams is not None:
            result += str(self.clams) + "\n"
        return result


# Helper standing in for the Java veggies printing loop; joins with ', '.
def _print_veggies(veggies: List[Veggies]) -> None:
    print("  veggies: " + ", ".join(str(v) for v in veggies))


# Concrete products: each holds only the factory and asks it for ingredients, so the
# same class yields NY or Chicago pizzas depending on the factory injected.
class CheesePizza2(Pizza2):
    def __init__(self, ingredient_factory: IngredientFactory) -> None:
        super().__init__()
        self.ingredient_factory = ingredient_factory

    def prepare(self) -> None:
        print("Preparing " + self.name)
        self.dough = self.ingredient_factory.create_dough()
        print("  dough: " + str(self.dough))
        self.sauce = self.ingredient_factory.create_sauce()
        print("  sauce: " + str(self.sauce))
        self.cheese = self.ingredient_factory.create_cheese()
        print("  cheese: " + str(self.cheese))


class ClamPizza2(Pizza2):
    def __init__(self, ingredient_factory: IngredientFactory) -> None:
        super().__init__()
        self.ingredient_factory = ingredient_factory

    def prepare(self) -> None:
        print("Preparing " + self.name)
        self.dough = self.ingredient_factory.create_dough()
        print("  dough: " + str(self.dough))
        self.sauce = self.ingredient_factory.create_sauce()
        print("  sauce: " + str(self.sauce))
        self.cheese = self.ingredient_factory.create_cheese()
        print("  cheese: " + str(self.cheese))
        self.clams = self.ingredient_factory.create_clam()
        print("  clams: " + str(self.clams))


class VeggiePizza2(Pizza2):
    def __init__(self, ingredient_factory: IngredientFactory) -> None:
        super().__init__()
        self.ingredient_factory = ingredient_factory

    def prepare(self) -> None:
        print("Preparing " + self.name)
        self.dough = self.ingredient_factory.create_dough()
        print("  dough: " + str(self.dough))
        self.sauce = self.ingredient_factory.create_sauce()
        print("  sauce: " + str(self.sauce))
        self.cheese = self.ingredient_factory.create_cheese()
        print("  cheese: " + str(self.cheese))
        self.veggies = self.ingredient_factory.create_veggies()
        _print_veggies(self.veggies)


class PepperoniPizza2(Pizza2):
    def __init__(self, ingredient_factory: IngredientFactory) -> None:
        super().__init__()
        self.ingredient_factory = ingredient_factory

    def prepare(self) -> None:
        print("Preparing " + self.name)
        self.dough = self.ingredient_factory.create_dough()
        print("  dough: " + str(self.dough))
        self.sauce = self.ingredient_factory.create_sauce()
        print("  sauce: " + str(self.sauce))
        self.cheese = self.ingredient_factory.create_cheese()
        print("  cheese: " + str(self.cheese))
        self.veggies = self.ingredient_factory.create_veggies()
        _print_veggies(self.veggies)
        self.pepperoni = self.ingredient_factory.create_pepperoni()
        print("  pepperoni: " + str(self.pepperoni))
