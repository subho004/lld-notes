// TurkeyAdapter: Object Adapter that presents a Turkey as a Duck (header-only).
#pragma once
#include <memory>
#include <utility>

#include "Duck.h"
#include "Turkey.h"

// Adapts a Turkey to the Duck interface (shares ownership of the adaptee).
class TurkeyAdapter : public Duck {
public:
    // shared_ptr: main keeps using the same turkey. std::move avoids a refcount bump.
    explicit TurkeyAdapter(std::shared_ptr<Turkey> turkey) : turkey(std::move(turkey)) {}

    void quack() override { turkey->gobble(); }
    // Turkeys fly short distances, so call fly 5 times to approximate a duck flight.
    void fly() override {
        for (int i = 0; i < 5; i++) {
            turkey->fly();
        }
    }

private:
    std::shared_ptr<Turkey> turkey;
};
