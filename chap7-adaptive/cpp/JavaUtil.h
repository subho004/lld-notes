#pragma once
// Tiny stand-ins for java.util.Enumeration / Iterator / Vector / ArrayList.
// Holds the two incompatible interfaces the adapters bridge; header-only because they are templates.
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

// Legacy interface (adaptee/target). Virtual destructor allows deleting via unique_ptr<Enumeration>.
template <typename T>
class Enumeration {
public:
    virtual ~Enumeration() = default;
    virtual bool hasMoreElements() = 0;
    virtual T nextElement() = 0;
};

// Modern interface (adaptee/target); remove() is optional and unsupported by default, as in Java.
template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual T next() = 0;
    virtual void remove() { throw std::logic_error("UnsupportedOperationException"); }
};

// Implementation details; the list classes hold a reference, so the Vector must outlive them.
namespace detail {
template <typename T>
class ListEnumeration : public Enumeration<T> {
public:
    explicit ListEnumeration(const std::vector<T>& items) : items(items) {}
    bool hasMoreElements() override { return i < items.size(); }
    T nextElement() override { return items[i++]; }

private:
    const std::vector<T>& items;
    std::size_t i = 0;
};

template <typename T>
class ListIterator : public Iterator<T> {
public:
    explicit ListIterator(const std::vector<T>& items) : items(items) {}
    bool hasNext() override { return i < items.size(); }
    T next() override { return items[i++]; }

private:
    const std::vector<T>& items;
    std::size_t i = 0;
};
}  // namespace detail

// Legacy collection that only offers an Enumeration; unique_ptr return transfers ownership to the caller.
template <typename T>
class Vector {
public:
    void add(const T& item) { items.push_back(item); }
    std::unique_ptr<Enumeration<T>> elements() const {
        return std::make_unique<detail::ListEnumeration<T>>(items);
    }

protected:  // shared with ArrayList, which derives from Vector
    std::vector<T> items;
};

// Modern collection; adds iterator(). Uses this->items because the base is a dependent template type.
template <typename T>
class ArrayList : public Vector<T> {
public:
    std::unique_ptr<Iterator<T>> iterator() const {
        return std::make_unique<detail::ListIterator<T>>(this->items);
    }
};
