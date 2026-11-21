"""Client for the Composite example: builds a tree of Menu2 nodes and MenuItem2 leaves."""
from menu_component import Menu2, MenuComponent, MenuItem2
from waitress2 import Waitress2


def main() -> None:
    pancake_house_menu: MenuComponent = Menu2("PANCAKE HOUSE MENU", "Breakfast")
    diner_menu: MenuComponent = Menu2("DINER MENU", "Lunch")
    cafe_menu: MenuComponent = Menu2("CAFE MENU", "Dinner")
    dessert_menu: MenuComponent = Menu2("DESSERT MENU", "Dessert of course!")

    # Menus are nested inside other menus; the Waitress only needs the root.
    all_menus: MenuComponent = Menu2("ALL MENUS", "All menus combined")
    all_menus.add(pancake_house_menu)
    all_menus.add(diner_menu)
    all_menus.add(dessert_menu)
    all_menus.add(cafe_menu)

    diner_menu.add(MenuItem2("Pasta", "Spaghetti with Marinara Sauce, and a slice of sourdough bread", True, 3.89))
    diner_menu.add(MenuItem2("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", True, 2.99))
    diner_menu.add(MenuItem2("BLT", "Bacon with lettuce & tomato on whole wheat", False, 2.99))
    diner_menu.add(MenuItem2("Soup of the day", "A bowl of the soup of the day, with a side of potato salad", False, 3.29))
    diner_menu.add(MenuItem2("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", False, 3.05))
    diner_menu.add(MenuItem2("Steamed Veggies and Brown Rice", "A medly of steamed vegetables over brown rice", True, 3.99))
    diner_menu.add(MenuItem2("Iced Tea", "Tea, Earl Grey... hot?", False, 1.89))

    waitress = Waitress2(all_menus)
    waitress.print_menu()


if __name__ == "__main__":
    main()
