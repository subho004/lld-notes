"""Client: sorting is a template method (list.sort) that calls back into Duck.__lt__."""
from typing import List

from duck import Duck


def print_ducks(ducks: List[Duck]) -> None:
    for duck in ducks:
        print(duck)


def main() -> None:
    ducks = [
        Duck("Daffy", 8),
        Duck("Dewey", 2),
        Duck("Howard", 7),
        Duck("Louie", 2),
        Duck("Donald", 10),
        Duck("Huey", 2),
    ]
    print("Before sorting:")
    print_ducks(ducks)
    ducks.sort()  # stable, uses Duck.__lt__ (like Arrays.sort on Comparable)
    print("\nAfter sorting:")
    print_ducks(ducks)


if __name__ == "__main__":
    main()
