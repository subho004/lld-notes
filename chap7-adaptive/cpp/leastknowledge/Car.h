// Principle of Least Knowledge demo: Car wraps Engine, Wheels and Doors (header-only).
#pragma once
#include <iostream>
#include <memory>
#include <utility>

// Component of Car; state is private so only Car (via methods) can change it.
class Engine {
public:
    void start() { running = true; std::cout << "Engine started\n"; }
    void stop() { running = false; std::cout << "Engine stopped\n"; }
    bool isRunning() const { return running; }

private:
    bool running = false;
};

// Component of Car.
class Wheels {
public:
    void rotate() { std::cout << "Wheels rotating\n"; }
    void stop() { std::cout << "Wheels stopped\n"; }
};

// Component of Car.
class Doors {
public:
    void lock() { locked = true; std::cout << "Doors locked\n"; }
    void unlock() { locked = false; std::cout << "Doors unlocked\n"; }
    bool isLocked() const { return locked; }

private:
    bool locked = false;
};

// Car owns its parts and is the only thing clients talk to (Law of Demeter).
// unique_ptr members: sole ownership, and no accessors, so parts cannot be reached from outside.
class Car {
public:
    Car(std::unique_ptr<Engine> engine, std::unique_ptr<Wheels> wheels, std::unique_ptr<Doors> doors)
        : engine(std::move(engine)), wheels(std::move(wheels)), doors(std::move(doors)) {}

    // Car coordinates its parts so the client does not have to.
    void start() {
        doors->unlock();
        engine->start();
    }

    void drive() {
        if (!engine->isRunning()) {
            std::cout << "Cannot drive - start the car first\n";
            return;
        }
        wheels->rotate();
        std::cout << "Driving...\n";
    }

    void stop() {
        wheels->stop();
        engine->stop();
    }

    void park() {
        stop();
        doors->lock();
        std::cout << "Parked\n";
    }

    void refuel() {
        if (engine->isRunning()) {
            std::cout << "Cannot refuel while engine is running\n";
            return;
        }
        std::cout << "Refueling...\n";
    }

private:
    std::unique_ptr<Engine> engine;
    std::unique_ptr<Wheels> wheels;
    std::unique_ptr<Doors> doors;
};
