/**
 * Client / entry point for the Iterator version: Waitress prints three menus with different storage.
 */
public class MenuTestDrive {
    public static void main(String args[]) {
        PancakeHouseMenu pancakeHouseMenu = new PancakeHouseMenu();
        DinnerMenu dinnerMenu = new DinnerMenu();
        CafeMenu cafeMenu = new CafeMenu();

        Waitress waitress = new Waitress(pancakeHouseMenu, dinnerMenu, cafeMenu);
        waitress.printMenu();
    }
}
