// Observer interface: notified with the duck that quacked.
#pragma once
#include "QuackObservable.h"

// Observer interface; the virtual destructor allows deletion through a base pointer.
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const QuackObservable& duck) = 0;
};
