/**
 * Client / entry point for the Composite version: builds a menu tree and prints it with one call.
 */
public class MenuTestDrive2 {
    public static void main(String[] args) {
        MenuComponent pancakeHouseMenu = new Menu2("PANCAKE HOUSE MENU", "Breakfast");
        MenuComponent dinerMenu = new Menu2("DINER MENU", "Lunch");
        MenuComponent cafeMenu = new Menu2("CAFE MENU", "Dinner");
        MenuComponent dessertMenu = new Menu2("DESSERT MENU", "Dessert of course!");

        MenuComponent allMenus = new Menu2("ALL MENUS", "All menus combined");
        allMenus.add(pancakeHouseMenu);
        allMenus.add(dinerMenu);
        allMenus.add(dessertMenu);
        allMenus.add(cafeMenu);

        dinerMenu.add(
                new MenuItem2("Pasta", "Spaghetti with Marinara Sauce, and a slice of sourdough bread", true, 3.89));
        dinerMenu.add(
                new MenuItem2("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99));
        dinerMenu.add(new MenuItem2("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99));
        dinerMenu.add(new MenuItem2("Soup of the day", "A bowl of the soup of the day, with a side of potato salad",
                false, 3.29));
        dinerMenu.add(
                new MenuItem2("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05));
        dinerMenu.add(new MenuItem2("Steamed Veggies and Brown Rice", "A medly of steamed vegetables over brown rice",
                true, 3.99));
        dinerMenu.add(new MenuItem2("Iced Tea", "Tea, Earl Grey... hot?", false, 1.89));

        // print() on the root recurses through the whole tree.
        Waitress2 waitress = new Waitress2(allMenus);
        waitress.printMenu();
    }
}
