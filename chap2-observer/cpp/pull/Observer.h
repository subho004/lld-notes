// Observer-pattern interfaces: Observer, DisplayElement and Subject.
// Header-only abstract classes (C++ equivalent of Java interfaces).
#pragma once
#include <memory>

// Observer role: update() takes no arguments; observers pull data from the subject.
// Virtual destructors let objects be deleted safely through a base pointer.
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

// Separate interface so rendering is independent of observing.
class DisplayElement {
public:
    virtual ~DisplayElement() = default;
    virtual void display() = 0;
};

// Subject role: register/remove observers and notify them of changes.
// The subject only keeps weak_ptr to its observers: it observes them without
// owning them, so there is no ownership cycle (observer -> subject -> observer).
class Subject {
public:
    virtual ~Subject() = default;
    virtual void registerObserver(const std::shared_ptr<Observer>& o) = 0;
    virtual void removeObserver(const std::shared_ptr<Observer>& o) = 0;
    virtual void notifyObservers() = 0;
};
