"""Waitress2: Composite client; it sees only the MenuComponent interface."""
from menu_component import MenuComponent


class Waitress2:
    def __init__(self, all_menus: MenuComponent) -> None:
        self.all_menus = all_menus

    def print_menu(self) -> None:
        # One call prints the whole tree, whatever its depth.
        self.all_menus.print()
