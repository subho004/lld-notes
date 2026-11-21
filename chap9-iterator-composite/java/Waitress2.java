/**
 * Client of the Composite pattern: treats the root MenuComponent uniformly, whether it is a menu or an item.
 */
public class Waitress2 {
    MenuComponent allMenus;

    public Waitress2(MenuComponent allMenus) {
        this.allMenus = allMenus;
    }

    // Delegates to the composite; recursion happens inside the tree.
    public void printMenu() {
        allMenus.print();
    }
}
