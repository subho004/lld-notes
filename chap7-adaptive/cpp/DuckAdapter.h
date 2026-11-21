// DuckAdapter: Object Adapter that presents a Duck as a Turkey (header-only).
#pragma once
#include <memory>
#include <utility>

#include "Duck.h"
#include "Turkey.h"

// Adapts a Duck to the Turkey interface (shares ownership of the adaptee).
class DuckAdapter : public Turkey {
public:
    // shared_ptr: the caller may keep using the same duck. std::move avoids a refcount bump.
    explicit DuckAdapter(std::shared_ptr<Duck> duck) : duck(std::move(duck)) {}

    void gobble() override { duck->quack(); }
    // A turkey flies only a short distance, so the duck flies 5 times to match.
    void fly() override {
        for (int i = 0; i < 5; i++) {
            duck->fly();
        }
    }

private:
    std::shared_ptr<Duck> duck;
};
