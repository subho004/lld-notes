/**
 * Client of the Iterator pattern: depends only on Menu and Iterator, never on concrete menus.
 */
public class Waitress {
    Menu pancakeHouseMenu;
    Menu dinnerMenu;
    Menu cafeMenu;

    public Waitress(Menu pancakeHouseMenu, Menu dinnerMenu, Menu cafeMenu) {
        this.pancakeHouseMenu = pancakeHouseMenu;
        this.dinnerMenu = dinnerMenu;
        this.cafeMenu = cafeMenu;
    }

    public void printMenu() {
        Iterator pancakeIterator = pancakeHouseMenu.createIterator();
        Iterator dinerIterator = dinnerMenu.createIterator();
        Iterator cafeIterator = cafeMenu.createIterator();

        System.out.println("MENU\n---\nBREAKFAST");
        printMenu(pancakeIterator);
        System.out.println("\nLUNCH");
        printMenu(dinerIterator);
        System.out.println("\nDINNER");
        printMenu(cafeIterator);
    }

    // One loop works for every menu, whatever its underlying collection.
    private void printMenu(Iterator iterator) {
        while (iterator.hasNext()) {
            MenuItem menuItem = iterator.next();
            System.out.print(menuItem.getName() + ", ");
            System.out.print(menuItem.getPrice() + " -- ");
            System.out.println(menuItem.getDescription());
        }
    }
}
