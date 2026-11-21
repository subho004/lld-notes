"""Simple Factory: SamplePizzaFactory."""
from typing import Optional

from pizza import CheesePizza, ClamPizza, PepperoniPizza, Pizza, VeggiePizza


# Simple Factory (a warm-up idiom, not a GoF pattern): encapsulates the creation
# if/else. Ported for completeness; no entry point uses it, as in Java.
class SamplePizzaFactory:
    def create_pizza(self, type: str) -> Optional[Pizza]:
        pizza: Optional[Pizza] = None
        if type == "cheese":
            pizza = CheesePizza()
        elif type == "pepperoni":
            pizza = PepperoniPizza()
        elif type == "clam":
            pizza = ClamPizza()
        elif type == "veggie":
            pizza = VeggiePizza()
        return pizza
