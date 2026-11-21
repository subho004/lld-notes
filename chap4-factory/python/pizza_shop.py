"""Entry point: Factory Method demo. Client code talks only to the PizzaStore abstraction."""
from pizza_store import CaliforniaStylePizzaStore, NYStylePizzaStore, PizzaStore


def main() -> None:
    ny_store: PizzaStore = NYStylePizzaStore()
    california_store: PizzaStore = CaliforniaStylePizzaStore()

    pizza = ny_store.order_pizza("cheese")
    print("Ethan ordered a " + pizza.get_name() + "\n")

    pizza = california_store.order_pizza("cheese")
    print("Joel ordered a " + pizza.get_name() + "\n")


if __name__ == "__main__":
    main()
