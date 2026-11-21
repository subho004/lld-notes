"""Aggregates of the Iterator example: Menu (Aggregate interface) and three concrete menus.

Each menu keeps its items in a different structure but exposes create_iterator().
"""
from abc import ABC, abstractmethod
from typing import Dict, List, Optional

from iterator import (CafeMenuIterator, DinerMenuIterator, Iterator,
                      PancakeHouseIterator)
from menu_item import MenuItem


class Menu(ABC):
    """Aggregate interface: a factory method that returns an Iterator."""

    @abstractmethod
    def create_iterator(self) -> Iterator: ...

    # Native protocol: `for item in menu:` works for every concrete menu.
    def __iter__(self):
        return iter(self.create_iterator())


class PancakeHouseMenu(Menu):
    """Concrete Aggregate backed by a list."""

    def __init__(self) -> None:
        self.menu_items: List[MenuItem] = []
        self.add_item("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", True, 2.99)
        self.add_item("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", False, 2.99)
        self.add_item("Blueberry Pancakes", "Pancakes made with fresh blueberries", True, 3.49)
        self.add_item("Waffles", "Waffles, with your choice of blueberries or strawberries", True, 3.99)

    def add_item(self, name: str, description: str, vegetarian: bool, price: float) -> None:
        self.menu_items.append(MenuItem(name, description, vegetarian, price))

    # Factory method: callers get an Iterator without knowing the storage.
    def create_iterator(self) -> Iterator:
        return PancakeHouseIterator(self.menu_items)


class DinnerMenu(Menu):
    """Concrete Aggregate backed by a fixed-size list (mirrors Java's array) with None for empty slots."""

    MAX_ITEMS = 6

    def __init__(self) -> None:
        self.number_of_items = 0
        self.menu_items: List[Optional[MenuItem]] = [None] * DinnerMenu.MAX_ITEMS
        self.add_item("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", True, 2.99)
        self.add_item("BLT", "Bacon with lettuce & tomato on whole wheat", False, 2.99)
        self.add_item("Soup of the day", "Soup of the day, with a side of potato salad", False, 3.29)
        self.add_item("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", False, 3.05)

    def add_item(self, name: str, description: str, vegetarian: bool, price: float) -> None:
        menu_item = MenuItem(name, description, vegetarian, price)
        if self.number_of_items >= DinnerMenu.MAX_ITEMS:
            import sys
            print("Sorry, menu is full! Can't add item to menu", file=sys.stderr)
        else:
            self.menu_items[self.number_of_items] = menu_item
            self.number_of_items = self.number_of_items + 1

    def create_iterator(self) -> Iterator:
        return DinerMenuIterator(self.menu_items)

    def __str__(self) -> str:
        return "Dinner Menu"


class CafeMenu(Menu):
    """Concrete Aggregate backed by a dict (Java: HashMap)."""

    def __init__(self) -> None:
        self.menu_items: Dict[str, MenuItem] = {}
        self.add_item("Veggie Burger and Air Fries", "Veggie burger on a whole wheat bun, lettuce, tomato, and fries", True, 3.99)
        self.add_item("Soup of the day", "A cup of the soup of the day, with a side salad", False, 3.69)
        self.add_item("Burrito", "A large burrito, with whole pinto beans, salsa, guacamole", True, 4.29)

    def add_item(self, name: str, description: str, vegetarian: bool, price: float) -> None:
        self.menu_items[name] = MenuItem(name, description, vegetarian, price)

    def create_iterator(self) -> Iterator:
        return CafeMenuIterator(self.menu_items)
