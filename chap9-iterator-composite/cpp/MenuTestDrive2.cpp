// Client for the Composite example: builds a tree of Menu2 nodes and MenuItem2 leaves.
// shared_ptr lets main() keep handles to menus that are also owned by their parent.
#include <memory>

#include "MenuComponent.h"
#include "Waitress2.h"

int main() {
    std::shared_ptr<MenuComponent> pancakeHouseMenu = std::make_shared<Menu2>("PANCAKE HOUSE MENU", "Breakfast");
    std::shared_ptr<MenuComponent> dinerMenu = std::make_shared<Menu2>("DINER MENU", "Lunch");
    std::shared_ptr<MenuComponent> cafeMenu = std::make_shared<Menu2>("CAFE MENU", "Dinner");
    std::shared_ptr<MenuComponent> dessertMenu = std::make_shared<Menu2>("DESSERT MENU", "Dessert of course!");

    // The root menu contains the other menus; the Waitress only needs the root.
    std::shared_ptr<MenuComponent> allMenus = std::make_shared<Menu2>("ALL MENUS", "All menus combined");
    allMenus->add(pancakeHouseMenu);
    allMenus->add(dinerMenu);
    allMenus->add(dessertMenu);
    allMenus->add(cafeMenu);

    dinerMenu->add(std::make_shared<MenuItem2>("Pasta", "Spaghetti with Marinara Sauce, and a slice of sourdough bread", true, 3.89));
    dinerMenu->add(std::make_shared<MenuItem2>("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99));
    dinerMenu->add(std::make_shared<MenuItem2>("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99));
    dinerMenu->add(std::make_shared<MenuItem2>("Soup of the day", "A bowl of the soup of the day, with a side of potato salad", false, 3.29));
    dinerMenu->add(std::make_shared<MenuItem2>("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05));
    dinerMenu->add(std::make_shared<MenuItem2>("Steamed Veggies and Brown Rice", "A medly of steamed vegetables over brown rice", true, 3.99));
    dinerMenu->add(std::make_shared<MenuItem2>("Iced Tea", "Tea, Earl Grey... hot?", false, 1.89));

    Waitress2 waitress(allMenus);
    waitress.printMenu();
    return 0;
}
