"""Client for ChocolateBoiler: checks the Singleton and walks fill -> boil -> drain."""
from chocolate_boiler import ChocolateBoiler


# Java prints booleans as true/false; lower-case str(bool) to match its output.
def _b(v: bool) -> str:
    return str(v).lower()


def main() -> None:
    boiler = ChocolateBoiler.get_instance()
    same_boiler = ChocolateBoiler.get_instance()

    print("Same instance? " + _b(boiler is same_boiler))

    boiler.fill()
    print(f"Empty: {_b(boiler.is_empty())}, Boiled: {_b(boiler.is_boiled())}")

    boiler.boil()
    print(f"Empty: {_b(boiler.is_empty())}, Boiled: {_b(boiler.is_boiled())}")

    boiler.drain()
    print(f"Empty: {_b(boiler.is_empty())}, Boiled: {_b(boiler.is_boiled())}")


if __name__ == "__main__":
    main()
