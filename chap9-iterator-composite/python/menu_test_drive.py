"""Client for the Iterator example: builds the three menus and hands them to the Waitress."""
from menu import CafeMenu, DinnerMenu, PancakeHouseMenu
from waitress import Waitress


def main() -> None:
    pancake_house_menu = PancakeHouseMenu()
    dinner_menu = DinnerMenu()
    cafe_menu = CafeMenu()

    waitress = Waitress(pancake_house_menu, dinner_menu, cafe_menu)
    waitress.print_menu()


if __name__ == "__main__":
    main()
