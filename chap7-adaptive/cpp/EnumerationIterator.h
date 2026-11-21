// EnumerationIterator<T>: Adapter exposing an Enumeration as an Iterator (templates, so header-only).
#pragma once
#include <memory>
#include <stdexcept>
#include <utility>

#include "JavaUtil.h"

// Adapts an Enumeration to the Iterator interface.
template <typename T>
class EnumerationIterator : public Iterator<T> {
public:
    // unique_ptr: the adapter is the sole owner of the adaptee and frees it with itself.
    explicit EnumerationIterator(std::unique_ptr<Enumeration<T>> enumeration)
        : enumeration(std::move(enumeration)) {}

    bool hasNext() override { return enumeration->hasMoreElements(); }
    T next() override { return enumeration->nextElement(); }
    // Enumeration cannot remove, so this is unsupported (Java: UnsupportedOperationException).
    void remove() override { throw std::logic_error("UnsupportedOperationException"); }

private:
    std::unique_ptr<Enumeration<T>> enumeration;
};
