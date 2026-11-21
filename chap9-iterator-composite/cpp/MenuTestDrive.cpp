// Client for the Iterator example: builds the three menus and hands them to the Waitress.
// The menus live on the stack here and outlive the iterators the Waitress creates.
#include "Menu.h"
#include "Waitress.h"

int main() {
    PancakeHouseMenu pancakeHouseMenu;
    DinnerMenu dinnerMenu;
    CafeMenu cafeMenu;

    Waitress waitress(pancakeHouseMenu, dinnerMenu, cafeMenu);
    waitress.printMenu();
    return 0;
}
