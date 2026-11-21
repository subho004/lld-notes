"""Client: passes a DuckAdapter to code that only knows the Turkey interface."""
from duck import MallardDuck
from duck_adapter import DuckAdapter
from turkey import Turkey, WildTurkey


def test_turkey(turkey: Turkey) -> None:
    # Depends only on the Turkey interface, so a DuckAdapter works here too.
    turkey.gobble()
    turkey.fly()


def main() -> None:
    duck = MallardDuck()
    turkey = WildTurkey()
    duck_adapter: Turkey = DuckAdapter(duck)

    print("The Duck says...")
    test_turkey(turkey)

    print("\nThe TurkeyAdapter says...")
    test_turkey(duck_adapter)


if __name__ == "__main__":
    main()
