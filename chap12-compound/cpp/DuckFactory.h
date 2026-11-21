// Concrete Factory: creates plain, undecorated ducks.
#pragma once
#include "AbstractDuckFactory.h"
#include "DuckCall.h"
#include "MallardDuck.h"
#include "RedheadDuck.h"
#include "RubberDuck.h"

// Concrete Factory.
class DuckFactory : public AbstractDuckFactory {
public:
    std::shared_ptr<Quackable> createMallardDuck() override { return std::make_shared<MallardDuck>(); }
    std::shared_ptr<Quackable> createRedheadDuck() override { return std::make_shared<RedheadDuck>(); }
    std::shared_ptr<Quackable> createDuckCall() override { return std::make_shared<DuckCall>(); }
    std::shared_ptr<Quackable> createRubberDuck() override { return std::make_shared<RubberDuck>(); }
};
