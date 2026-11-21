"""Entry point: Abstract Factory demo. The same order yields different ingredients per store."""
from pizza_store2 import ChicagoPizzaStore2, NYPizzaStore2, PizzaStore2


def main() -> None:
    ny_store: PizzaStore2 = NYPizzaStore2()
    chicago_store: PizzaStore2 = ChicagoPizzaStore2()

    print("=== Same pizza type, different ingredient factories ===\n")

    pizza = ny_store.order_pizza("cheese")
    print("Ethan ordered a " + pizza.get_name())
    print(pizza)

    pizza = chicago_store.order_pizza("cheese")
    print("Joel ordered a " + pizza.get_name())
    print(pizza)

    print("=== Full factory usage (veggies, pepperoni, clams) ===\n")

    pizza = ny_store.order_pizza("veggie")
    print("Ethan ordered a " + pizza.get_name())
    print(pizza)

    pizza = chicago_store.order_pizza("pepperoni")
    print("Joel ordered a " + pizza.get_name())
    print(pizza)

    pizza = ny_store.order_pizza("clam")
    print("Ethan ordered a " + pizza.get_name())
    print(pizza)

    pizza = chicago_store.order_pizza("clam")
    print("Joel ordered a " + pizza.get_name())
    print(pizza)


if __name__ == "__main__":
    main()
