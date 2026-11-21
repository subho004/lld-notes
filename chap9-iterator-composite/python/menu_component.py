"""Composite pattern: MenuComponent (Component), MenuItem2 (Leaf) and Menu2 (Composite)."""
from typing import List


class MenuComponent:
    """Composite pattern: common interface for leaves (MenuItem2) and nodes (Menu2).
    Unsupported operations raise, exactly like the Java default implementations."""

    def add(self, menu_component: "MenuComponent") -> None:
        raise NotImplementedError("UnsupportedOperationException")

    def remove(self, menu_component: "MenuComponent") -> None:
        raise NotImplementedError("UnsupportedOperationException")

    def get_child(self, i: int) -> "MenuComponent":
        raise NotImplementedError("UnsupportedOperationException")

    def get_name(self) -> str:
        raise NotImplementedError("UnsupportedOperationException")

    def get_description(self) -> str:
        raise NotImplementedError("UnsupportedOperationException")

    def get_price(self) -> float:
        raise NotImplementedError("UnsupportedOperationException")

    def is_vegetarian(self) -> bool:
        raise NotImplementedError("UnsupportedOperationException")

    def print(self) -> None:
        raise NotImplementedError("UnsupportedOperationException")


class MenuItem2(MenuComponent):
    """Leaf: overrides only the operations that make sense for a single item."""

    def __init__(self, name: str, description: str, vegetarian: bool, price: float) -> None:
        self.name = name
        self.description = description
        self.vegetarian = vegetarian
        self.price = price

    def get_name(self) -> str:
        return self.name

    def get_description(self) -> str:
        return self.description

    def get_price(self) -> float:
        return self.price

    def is_vegetarian(self) -> bool:
        return self.vegetarian

    def print(self) -> None:
        print(" " + self.get_name(), end="")
        if self.is_vegetarian():
            print("(v)", end="")
        print(", " + str(self.get_price()))
        print("    -- " + self.get_description())


class Menu2(MenuComponent):
    """Composite: holds child MenuComponents (items or sub-menus) and forwards print() to them."""

    def __init__(self, name: str, description: str) -> None:
        self.menu_components: List[MenuComponent] = []
        self.name = name
        self.description = description

    def add(self, menu_component: MenuComponent) -> None:
        self.menu_components.append(menu_component)

    def remove(self, menu_component: MenuComponent) -> None:
        self.menu_components.remove(menu_component)

    def get_child(self, i: int) -> MenuComponent:
        return self.menu_components[i]

    def get_name(self) -> str:
        return self.name

    def get_description(self) -> str:
        return self.description

    def print(self) -> None:
        print(self.get_name() + ", " + self.get_description())
        print("--------------------------------")
        # Recursion: a child may itself be a Menu2, so the whole subtree prints.
        for menu_component in self.menu_components:
            menu_component.print()

    # Native protocol: iterate over direct children.
    def __iter__(self):
        return iter(self.menu_components)
