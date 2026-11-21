#pragma once
// Aggregates of the Iterator example: Menu (interface) and three concrete menus.
#include <array>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Iterator.h"
#include "Iterators.h"

// Aggregate interface: createIterator() is the factory method.
class Menu {
public:
    virtual ~Menu() = default;
    // Returns unique_ptr: the caller owns the new iterator.
    virtual std::unique_ptr<Iterator> createIterator() = 0;
};

// Concrete Aggregate backed by a vector.
class PancakeHouseMenu : public Menu {
    std::vector<MenuItemPtr> menuItems;

public:
    PancakeHouseMenu() {
        addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
        addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
        addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
        addItem("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.99);
    }
    void addItem(const std::string& name, const std::string& description, bool vegetarian, double price) {
        menuItems.push_back(std::make_shared<MenuItem>(name, description, vegetarian, price));
    }
    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<PancakeHouseIterator>(menuItems);
    }
    // STL-style iteration: for (auto& item : menu)
    std::vector<MenuItemPtr>::const_iterator begin() const { return menuItems.begin(); }
    std::vector<MenuItemPtr>::const_iterator end() const { return menuItems.end(); }
};

// Concrete Aggregate backed by a fixed std::array (Java: MenuItem[]); empty slots are nullptr.
class DinnerMenu : public Menu {
public:
    static constexpr std::size_t MAX_ITEMS = 6;

private:
    std::size_t numberOfItems = 0;
    std::array<MenuItemPtr, MAX_ITEMS> menuItems;

public:
    // STL-style forward iterator that stops at the first empty slot.
    class StlIterator {
        const std::array<MenuItemPtr, MAX_ITEMS>* items;
        std::size_t pos;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = MenuItemPtr;
        using difference_type = std::ptrdiff_t;
        using pointer = const MenuItemPtr*;
        using reference = const MenuItemPtr&;
        StlIterator(const std::array<MenuItemPtr, MAX_ITEMS>* items, std::size_t pos) : items(items), pos(pos) {}
        reference operator*() const { return (*items)[pos]; }
        pointer operator->() const { return &(*items)[pos]; }
        StlIterator& operator++() { ++pos; return *this; }
        StlIterator operator++(int) { StlIterator t = *this; ++pos; return t; }
        bool operator==(const StlIterator& o) const { return pos == o.pos; }
        bool operator!=(const StlIterator& o) const { return pos != o.pos; }
    };

    DinnerMenu() {
        addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
        addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
        addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
        addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
    }
    void addItem(const std::string& name, const std::string& description, bool vegetarian, double price) {
        auto menuItem = std::make_shared<MenuItem>(name, description, vegetarian, price);
        if (numberOfItems >= MAX_ITEMS) {
            std::cerr << "Sorry, menu is full! Can't add item to menu\n";
        } else {
            menuItems[numberOfItems] = menuItem;
            numberOfItems = numberOfItems + 1;
        }
    }
    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<DinerMenuIterator<MAX_ITEMS>>(menuItems);
    }
    // end() uses numberOfItems, so range-for stops before the empty slots.
    StlIterator begin() const { return StlIterator(&menuItems, 0); }
    StlIterator end() const { return StlIterator(&menuItems, numberOfItems); }
    std::string toString() const { return "Dinner Menu"; }
};

// Concrete Aggregate; a vector of pairs stands in for Java's HashMap.
class CafeMenu : public Menu {
    // Insertion-ordered entries standing in for Java's HashMap<String, MenuItem>.
    std::vector<std::pair<std::string, MenuItemPtr>> menuItems;

public:
    CafeMenu() {
        addItem("Veggie Burger and Air Fries", "Veggie burger on a whole wheat bun, lettuce, tomato, and fries", true, 3.99);
        addItem("Soup of the day", "A cup of the soup of the day, with a side salad", false, 3.69);
        addItem("Burrito", "A large burrito, with whole pinto beans, salsa, guacamole", true, 4.29);
    }
    void addItem(const std::string& name, const std::string& description, bool vegetarian, double price) {
        auto menuItem = std::make_shared<MenuItem>(name, description, vegetarian, price);
        for (auto& e : menuItems) {
            if (e.first == name) { e.second = menuItem; return; }  // put() replaces
        }
        menuItems.emplace_back(name, menuItem);
    }
    std::unique_ptr<Iterator> createIterator() override {
        return std::make_unique<CafeMenuIterator>(menuItems);
    }
};
