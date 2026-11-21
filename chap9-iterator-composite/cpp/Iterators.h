#pragma once
// Concrete Iterators, one per menu storage type (vector, std::array, key/value list).
#include <array>
#include <iterator>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

#include "Iterator.h"
#include "JavaHashOrder.h"

using MenuItemPtr = std::shared_ptr<MenuItem>;

// The iterators below hold a non-owning pointer to the menu's storage
// (like Java's shared reference); the menu must outlive its iterators.

// Concrete Iterator over a std::vector.
class PancakeHouseIterator : public Iterator {
    const std::vector<MenuItemPtr>* items;
    std::size_t position = 0;

public:
    explicit PancakeHouseIterator(const std::vector<MenuItemPtr>& items) : items(&items) {}
    MenuItemPtr next() override {
        MenuItemPtr menuItem = (*items)[position];
        position = position + 1;
        return menuItem;
    }
    bool hasNext() override { return position < items->size(); }
};

// Concrete Iterator over a fixed std::array; N is the array size, so no size is stored.
template <std::size_t N>
class DinerMenuIterator : public Iterator {
    const std::array<MenuItemPtr, N>* items;
    std::size_t position = 0;

public:
    explicit DinerMenuIterator(const std::array<MenuItemPtr, N>& items) : items(&items) {}
    MenuItemPtr next() override { return (*items)[position++]; }
    // A null slot marks the end of the real items.
    bool hasNext() override { return position < N && (*items)[position] != nullptr; }
    void remove() { throw std::runtime_error("You shouldn't be trying to remove menu items"); }
};

// Concrete Iterator visiting every other slot; unused by the demos.
template <std::size_t N>
class AlternatingDinerMenuIterator : public Iterator {
    const std::array<MenuItemPtr, N>* items;
    std::size_t position;

public:
    static constexpr int DAY_OF_WEEK = 7;  // java.util.Calendar.DAY_OF_WEEK constant
    explicit AlternatingDinerMenuIterator(const std::array<MenuItemPtr, N>& items)
        : items(&items), position(DAY_OF_WEEK % 2) {}
    MenuItemPtr next() override {
        MenuItemPtr menuItem = (*items)[position];
        position = position + 2;
        return menuItem;
    }
    bool hasNext() override { return !(position >= N || (*items)[position] == nullptr); }
    void remove() { throw std::runtime_error("Alternating Diner Menu Iterator does not support remove()"); }
};

// Iterates a snapshot of a "hash map" in Java HashMap order.
class CafeMenuIterator : public Iterator {
    std::vector<MenuItemPtr> ordered;
    std::vector<MenuItemPtr>::const_iterator iterator;

public:
    explicit CafeMenuIterator(const std::vector<std::pair<std::string, MenuItemPtr>>& entries) {
        std::vector<std::string> keys;
        for (const auto& e : entries) keys.push_back(e.first);
        // Copy items into Java HashMap order up front, so later menu changes do not affect this iterator.
        for (std::size_t i : javaHashMapOrder(keys)) ordered.push_back(entries[i].second);
        iterator = ordered.begin();
    }
    MenuItemPtr next() override { return *iterator++; }
    bool hasNext() override { return iterator != ordered.end(); }
};
