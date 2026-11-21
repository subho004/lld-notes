"""Client for Singleton: two get_instance() calls must return the same object."""
from singleton import Singleton


def main() -> None:
    first = Singleton.get_instance()
    second = Singleton.get_instance()
    print("Same instance? " + str(first is second).lower())


if __name__ == "__main__":
    main()
