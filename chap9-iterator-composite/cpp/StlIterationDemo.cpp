// Extra (not in the Java book code): STL-style begin()/end() iteration next to
// the book-style hasNext()/next() iterator.
#include <algorithm>
#include <iostream>

#include "Menu.h"
#include "MenuComponent.h"

int main() {
    PancakeHouseMenu pancake;
    DinnerMenu diner;

    std::cout << "Book style (hasNext/next):\n";
    auto it = pancake.createIterator();
    while (it->hasNext()) std::cout << "  " << it->next()->getName() << "\n";

    std::cout << "STL style (range-for over PancakeHouseMenu):\n";
    for (const auto& item : pancake) std::cout << "  " << item->getName() << "\n";

    std::cout << "STL style over DinnerMenu (skips empty slots):\n";
    for (const auto& item : diner) std::cout << "  " << item->getName() << "\n";

    std::cout << "Works with <algorithm>:\n";
    auto cheapest = std::min_element(pancake.begin(), pancake.end(),
                                     [](const MenuItemPtr& a, const MenuItemPtr& b) { return a->getPrice() < b->getPrice(); });
    std::cout << "  cheapest: " << (*cheapest)->getName() << "\n";
    std::cout << "  items in diner: " << std::distance(diner.begin(), diner.end()) << "\n";

    std::cout << "Composite children via Menu2::begin/end:\n";
    Menu2 m("M", "d");
    m.add(std::make_shared<MenuItem2>("Tea", "hot", true, 1.5));
    m.add(std::make_shared<MenuItem2>("Cake", "sweet", false, 2.5));
    for (const auto& child : m) std::cout << "  " << child->getName() << "\n";
    return 0;
}
