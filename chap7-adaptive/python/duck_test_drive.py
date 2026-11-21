"""Client: passes a TurkeyAdapter to code that only knows the Duck interface."""
from duck import Duck, MallardDuck
from turkey import WildTurkey
from turkey_adapter import TurkeyAdapter


def test_duck(duck: Duck) -> None:
    # Depends only on the Duck interface, so it cannot tell a real duck from an adapter.
    duck.quack()
    duck.fly()


def main() -> None:
    duck = MallardDuck()
    turkey = WildTurkey()
    turkey_adapter: Duck = TurkeyAdapter(turkey)

    print("The Turkey says...")
    turkey.gobble()
    turkey.fly()

    print("\nThe Duck says...")
    test_duck(duck)

    print("\nThe TurkeyAdapter says...")
    test_duck(turkey_adapter)


if __name__ == "__main__":
    main()
