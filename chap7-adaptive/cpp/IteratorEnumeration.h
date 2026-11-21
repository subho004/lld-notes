// IteratorEnumeration<T>: Adapter exposing an Iterator as an Enumeration (templates, so header-only).
#pragma once
#include <memory>
#include <utility>

#include "JavaUtil.h"

// Adapts an Iterator to the Enumeration interface.
template <typename T>
class IteratorEnumeration : public Enumeration<T> {
public:
    // unique_ptr: the adapter is the sole owner of the adaptee and frees it with itself.
    explicit IteratorEnumeration(std::unique_ptr<Iterator<T>> iterator)
        : iterator(std::move(iterator)) {}

    bool hasMoreElements() override { return iterator->hasNext(); }
    T nextElement() override { return iterator->next(); }

private:
    std::unique_ptr<Iterator<T>> iterator;
};
