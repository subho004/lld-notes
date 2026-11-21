#pragma once
// Waitress2: Composite client; it holds only the root MenuComponent.
#include <memory>

#include "MenuComponent.h"

class Waitress2 {
    std::shared_ptr<MenuComponent> allMenus;

public:
    explicit Waitress2(std::shared_ptr<MenuComponent> allMenus) : allMenus(std::move(allMenus)) {}
    // One call prints the whole tree.
    void printMenu() const { allMenus->print(); }
};
