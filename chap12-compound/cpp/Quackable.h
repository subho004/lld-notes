// Quackable: common component interface for ducks, adapters, decorators and flocks.
#pragma once
#include "QuackObservable.h"

class Quackable : public QuackObservable {
public:
    virtual void quack() = 0;
};
