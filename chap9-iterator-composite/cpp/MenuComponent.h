#pragma once
// Composite pattern: MenuComponent (Component), MenuItem2 (Leaf), Menu2 (Composite).
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// Stands in for Java's UnsupportedOperationException.
struct UnsupportedOperationException : std::runtime_error {
    UnsupportedOperationException() : std::runtime_error("UnsupportedOperationException") {}
};

// Composite: common interface for leaves (MenuItem2) and nodes (Menu2).
class MenuComponent {
public:
    // Virtual destructor: children are destroyed through shared_ptr<MenuComponent>.
    virtual ~MenuComponent() = default;
    virtual void add(std::shared_ptr<MenuComponent>) { throw UnsupportedOperationException(); }
    virtual void remove(const std::shared_ptr<MenuComponent>&) { throw UnsupportedOperationException(); }
    virtual std::shared_ptr<MenuComponent> getChild(std::size_t) { throw UnsupportedOperationException(); }
    virtual std::string getName() const { throw UnsupportedOperationException(); }
    virtual std::string getDescription() const { throw UnsupportedOperationException(); }
    virtual double getPrice() const { throw UnsupportedOperationException(); }
    virtual bool isVegetarian() const { throw UnsupportedOperationException(); }
    virtual void print() const { throw UnsupportedOperationException(); }
};

// Leaf: overrides only the operations that apply to a single item.
class MenuItem2 : public MenuComponent {
    std::string name;
    std::string description;
    bool vegetarian;
    double price;

public:
    MenuItem2(std::string name, std::string description, bool vegetarian, double price)
        : name(std::move(name)), description(std::move(description)), vegetarian(vegetarian), price(price) {}
    std::string getName() const override { return name; }
    std::string getDescription() const override { return description; }
    double getPrice() const override { return price; }
    bool isVegetarian() const override { return vegetarian; }
    void print() const override {
        std::cout << " " << getName();
        if (isVegetarian()) std::cout << "(v)";
        std::cout << ", " << getPrice() << "\n";
        std::cout << "    -- " << getDescription() << "\n";
    }
};

// Composite: holds child components and forwards print() to each of them.
class Menu2 : public MenuComponent {
    // Parent owns children (shared_ptr so callers may keep handles, as in Java).
    std::vector<std::shared_ptr<MenuComponent>> menuComponents;
    std::string name;
    std::string description;

public:
    Menu2(std::string name, std::string description) : name(std::move(name)), description(std::move(description)) {}
    void add(std::shared_ptr<MenuComponent> menuComponent) override { menuComponents.push_back(std::move(menuComponent)); }
    void remove(const std::shared_ptr<MenuComponent>& menuComponent) override {
        auto it = std::find(menuComponents.begin(), menuComponents.end(), menuComponent);
        if (it != menuComponents.end()) menuComponents.erase(it);
    }
    std::shared_ptr<MenuComponent> getChild(std::size_t i) override { return menuComponents.at(i); }
    std::string getName() const override { return name; }
    std::string getDescription() const override { return description; }
    void print() const override {
        std::cout << getName() << ", " << getDescription() << "\n";
        std::cout << "--------------------------------\n";
        // Recursion: a child may itself be a Menu2.
        for (const auto& menuComponent : menuComponents) menuComponent->print();
    }
    // STL-style iteration over direct children.
    auto begin() const { return menuComponents.begin(); }
    auto end() const { return menuComponents.end(); }
};
