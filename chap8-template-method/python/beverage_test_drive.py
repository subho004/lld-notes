"""Client: runs both hook beverages through the same template method (reads y/n from stdin)."""
from coffee_with_hook import CoffeeWithHook
from tea_with_hook import TeaWithHook


def main() -> None:
    tea_hook = TeaWithHook()
    coffee_hook = CoffeeWithHook()

    print("\nMaking tea...")
    tea_hook.prepare_recipe()

    print("\nMaking coffee...")
    coffee_hook.prepare_recipe()


if __name__ == "__main__":
    main()
