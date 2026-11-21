"""Extra (not in the Java book code): Python's native iterator protocol.

Shows the book iterators, Menu and Menu2 working directly in for loops and with
built-ins such as max() and list().
"""
from menu import CafeMenu, DinnerMenu, PancakeHouseMenu
from menu_component import Menu2, MenuItem2


def main() -> None:
    print("for-loop over book-style Iterator (has __iter__/__next__):")
    for item in PancakeHouseMenu().create_iterator():
        print(" ", item.get_name())

    print("for-loop directly over a Menu (Menu.__iter__):")
    for menu in (DinnerMenu(), CafeMenu()):
        print(" ", [i.get_name() for i in menu])

    print("generic consumers work too:")
    prices = [i.get_price() for i in PancakeHouseMenu()]
    print("  max price:", max(prices), " total items:", len(list(DinnerMenu())))

    print("Composite children via Menu2.__iter__:")
    m = Menu2("M", "d")
    m.add(MenuItem2("Tea", "hot", True, 1.5))
    m.add(MenuItem2("Cake", "sweet", False, 2.5))
    for child in m:
        print(" ", child.get_name())


if __name__ == "__main__":
    main()
