"""Waitress: Iterator client; depends only on the Menu and Iterator interfaces."""
from iterator import Iterator
from menu import Menu


class Waitress:
    def __init__(self, pancake_house_menu: Menu, dinner_menu: Menu, cafe_menu: Menu) -> None:
        self.pancake_house_menu = pancake_house_menu
        self.dinner_menu = dinner_menu
        self.cafe_menu = cafe_menu

    def print_menu(self) -> None:
        pancake_iterator = self.pancake_house_menu.create_iterator()
        diner_iterator = self.dinner_menu.create_iterator()
        cafe_iterator = self.cafe_menu.create_iterator()

        print("MENU\n---\nBREAKFAST")
        self._print_menu(pancake_iterator)
        print("\nLUNCH")
        self._print_menu(diner_iterator)
        print("\nDINNER")
        self._print_menu(cafe_iterator)

    # Same loop for every menu, because it only uses the Iterator interface.
    def _print_menu(self, iterator: Iterator) -> None:
        while iterator.has_next():
            menu_item = iterator.next()
            print(menu_item.get_name() + ", ", end="")
            print(str(menu_item.get_price()) + " -- ", end="")
            print(menu_item.get_description())
