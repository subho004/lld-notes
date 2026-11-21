"""The 'dependent' pizza store: one class that knows every concrete pizza."""
from typing import Optional

from pizza import (
    ChicagoStyleCheesePizza, ChicagoStyleClamPizza,
    ChicagoStylePepperoniPizza, NYStyleCheesePizza, NYStyleClamPizza,
    NYStylePepperoniPizza, NYStyleVeggiePizza, Pizza,
)


# The 'before' picture: no Factory Method, so this one class depends on every
# concrete pizza. Chicago has no veggie pizza (as in the Java original).
class DependentPizzaStore:
    def create_pizza(self, region: str, type: str) -> Optional[Pizza]:
        pizza: Optional[Pizza] = None
        if region == "NY":
            if type == "cheese":
                pizza = NYStyleCheesePizza()
            elif type == "pepperoni":
                pizza = NYStylePepperoniPizza()
            elif type == "clam":
                pizza = NYStyleClamPizza()
            elif type == "veggie":
                pizza = NYStyleVeggiePizza()
        elif region == "Chicago":
            if type == "cheese":
                pizza = ChicagoStyleCheesePizza()
            elif type == "pepperoni":
                pizza = ChicagoStylePepperoniPizza()
            elif type == "clam":
                pizza = ChicagoStyleClamPizza()
        return pizza


# No null check: a None result would raise AttributeError, mirroring Java's NPE.
def main() -> None:
    store = DependentPizzaStore()

    ny_pizza = store.create_pizza("NY", "cheese")
    ny_pizza.prepare()
    print("Ordered: " + ny_pizza.get_name() + "\n")

    chicago_pizza = store.create_pizza("Chicago", "pepperoni")
    chicago_pizza.prepare()
    print("Ordered: " + chicago_pizza.get_name())


if __name__ == "__main__":
    main()
