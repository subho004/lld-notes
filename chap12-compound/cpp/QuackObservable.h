// Subject interface for quack observers (the Observer pattern).
#pragma once
#include <memory>
#include <string>

// Forward declaration: Observer.h includes this header, so including it here would be circular.
class Observer;

// Interface with a virtual destructor so ducks can be deleted through it.
class QuackObservable {
public:
    virtual ~QuackObservable() = default;
    // Observers are held weakly (the caller keeps ownership), so a duck never
    // keeps its quackologist alive and no ownership cycle can form.
    virtual void registerObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void notifyObservers() = 0;
    // Java's Object.toString()
    virtual std::string toString() const { return "Quackable"; }
};
