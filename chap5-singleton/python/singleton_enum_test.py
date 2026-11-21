"""Client for SingletonEnum: calls the method and checks identity of INSTANCE."""
from singleton_enum import SingletonEnum


def main() -> None:
    SingletonEnum.INSTANCE.do_something()
    another = SingletonEnum.INSTANCE
    print("Same instance? " + str(SingletonEnum.INSTANCE is another).lower())


if __name__ == "__main__":
    main()
