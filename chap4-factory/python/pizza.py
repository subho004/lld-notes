"""Pizza (string-based version) and all concrete pizzas."""
from abc import ABC
from typing import List


# Product base for the Factory Method / Simple Factory examples. Subclasses only
# fill in name, dough, sauce and toppings; prepare/bake/cut/box are shared steps.
class Pizza(ABC):
    def __init__(self) -> None:
        self.name: str = ""
        self.dough: str = ""
        self.sauce: str = ""
        self.toppings: List[str] = []

    def prepare(self) -> None:
        print("Preparing " + self.name)
        print("Tossing dough...")
        print("Adding sauce...")
        print("Adding toppings: ")
        for topping in self.toppings:
            print("    " + topping)

    def bake(self) -> None:
        print("Bake for 25 minutes at 350")

    def cut(self) -> None:
        print("Cutting the pizza into diagonal slices")

    def box(self) -> None:
        print("Place pizza in official PizzaStore box")

    def get_name(self) -> str:
        return self.name


# Python-only helper replacing the Java constructors' field assignments;
# the inherited attributes are filled in after super().__init__().
def _init(p: Pizza, name: str, dough: str, sauce: str, *toppings: str) -> None:
    p.name, p.dough, p.sauce = name, dough, sauce
    p.toppings.extend(toppings)


# ---- Simple factory pizzas ----
# Concrete products used by SamplePizzaFactory (the Simple Factory warm-up).
class CheesePizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "Cheese Pizza", "Regular Crust", "Marinara Pizza Sauce",
              "Fresh Mozzarella", "Parmesan")


class ClamPizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "Clam Pizza", "Thin Crust", "White Garlic Sauce",
              "Clams", "Grated parmesan cheese")


class PepperoniPizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "Pepperoni Pizza", "Regular Crust", "Marinara Pizza Sauce",
              "Sliced Pepperoni", "Sliced Onion", "Grated parmesan cheese")


class VeggiePizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "Veggie Pizza", "Crust", "Marinara Sauce",
              "Shredded mozzarella", "Diced onion", "Sliced mushrooms",
              "Sliced red pepper", "Sliced black olives")


# ---- New York style ----
# Concrete products created by NYStylePizzaStore / DependentPizzaStore.
class NYStyleCheesePizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "NY Style Sauce and Cheese Pizza", "Thin Crust Dough",
              "Marinara Sauce", "Grated Reggiano Cheese")


class NYStyleClamPizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "NY Style Clam Pizza", "Thin Crust Dough", "Marinara Sauce",
              "Grated Reggiano Cheese", "Fresh Clams from Long Island Sound")


class NYStylePepperoniPizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "NY Style Pepperoni Pizza", "Thin Crust Dough",
              "Marinara Sauce", "Grated Reggiano Cheese", "Sliced Pepperoni",
              "Garlic", "Onion", "Mushrooms", "Red Pepper")


class NYStyleVeggiePizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "NY Style Veggie Pizza", "Thin Crust Dough",
              "Marinara Sauce", "Grated Reggiano Cheese", "Garlic", "Onion",
              "Mushrooms", "Red Pepper")


# ---- Chicago style ----
# Chicago pizzas override cut() to use square slices, the only behavioral difference.
class ChicagoStyleCheesePizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "Chicago Style Deep Dish Cheese Pizza",
              "Extra Thick Crust Dough", "Plum Tomato Sauce",
              "Shredded Mozzarella Cheese")

    def cut(self) -> None:
        print("Cutting the pizza into square slices")


class ChicagoStyleClamPizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "Chicago Style Deep Dish Clam Pizza",
              "Extra Thick Crust Dough", "Plum Tomato Sauce",
              "Shredded Mozzarella Cheese", "Fresh Clams")

    def cut(self) -> None:
        print("Cutting the pizza into square slices")


class ChicagoStylePepperoniPizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "Chicago Style Deep Dish Pepperoni Pizza",
              "Extra Thick Crust Dough", "Plum Tomato Sauce",
              "Shredded Mozzarella Cheese", "Sliced Pepperoni")

    def cut(self) -> None:
        print("Cutting the pizza into square slices")


# ---- California style ----
# Concrete products created by CaliforniaStylePizzaStore.
class CaliforniaStyleCheesePizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "California Style Cheese Pizza", "Very Thin Crust Dough",
              "Bruschetta Sauce", "Goat Cheese", "Fresh Mozzarella")


class CaliforniaStyleClamPizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "California Style Clam Pizza", "Very Thin Crust Dough",
              "White Wine Sauce", "Fresh Clams", "Garlic", "Lemon Zest")


class CaliforniaStylePepperoniPizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "California Style Pepperoni Pizza", "Very Thin Crust Dough",
              "Bruschetta Sauce", "Goat Cheese", "Artisan Pepperoni", "Arugula")


class CaliforniaStyleVeggiePizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        _init(self, "California Style Veggie Pizza", "Very Thin Crust Dough",
              "Pesto Sauce", "Goat Cheese", "Avocado", "Sundried Tomato",
              "Spinach")
