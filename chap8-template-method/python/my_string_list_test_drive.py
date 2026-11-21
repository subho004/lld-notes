"""Client: iterates a MyStringList and a sub-list view, both using inherited template methods."""
from my_string_list import MyStringList


def main() -> None:
    ducks = ["Mallard Duck", "Redhead Duck", "Rubber Duck", "Decoy Duck"]
    ducks_list = MyStringList(ducks)
    ducks_sub_list = ducks_list.sub_list(2, 3)

    print("Full list:")
    for duck in ducks_list:
        print(duck)

    print("\nSublist (index 2, one item):")
    for duck in ducks_sub_list:
        print(duck)


if __name__ == "__main__":
    main()
