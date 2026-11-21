#pragma once
// Iterator interface (pattern role: Iterator). Header-only.
#include <memory>

#include "MenuItem.h"

// Book-style iterator: hasNext()/next().
class Iterator {
public:
    // Virtual destructor: iterators are deleted through unique_ptr<Iterator>.
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual std::shared_ptr<MenuItem> next() = 0;
};
