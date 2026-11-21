#pragma once
// Waitress: Iterator client; it uses only the Menu and Iterator interfaces.
#include <iostream>

#include "Menu.h"

class Waitress {
    Menu* pancakeHouseMenu;  // non-owning: menus are owned by the caller
    Menu* dinnerMenu;
    Menu* cafeMenu;

    // Takes a reference: the caller keeps ownership of the iterator.
    void printMenu(Iterator& iterator) {
        while (iterator.hasNext()) {
            MenuItemPtr menuItem = iterator.next();
            std::cout << menuItem->getName() << ", ";
            std::cout << menuItem->getPrice() << " -- ";
            std::cout << menuItem->getDescription() << "\n";
        }
    }

public:
    Waitress(Menu& pancakeHouseMenu, Menu& dinnerMenu, Menu& cafeMenu)
        : pancakeHouseMenu(&pancakeHouseMenu), dinnerMenu(&dinnerMenu), cafeMenu(&cafeMenu) {}

    void printMenu() {
        auto pancakeIterator = pancakeHouseMenu->createIterator();
        auto dinerIterator = dinnerMenu->createIterator();
        auto cafeIterator = cafeMenu->createIterator();

        std::cout << "MENU\n---\nBREAKFAST\n";
        printMenu(*pancakeIterator);
        std::cout << "\nLUNCH\n";
        printMenu(*dinerIterator);
        std::cout << "\nDINNER\n";
        printMenu(*cafeIterator);
    }
};
