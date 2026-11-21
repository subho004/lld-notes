"""Client for ChocoholicEnum: shows the single-member Enum is one shared instance."""
from chocoholic_enum import ChocoholicEnum


def main() -> None:
    ChocoholicEnum.INSTANCE.eat_chocolate()
    another = ChocoholicEnum.INSTANCE
    print("Same instance? " + str(ChocoholicEnum.INSTANCE is another).lower())


if __name__ == "__main__":
    main()
