// Subject interface for HeartModel, the "incompatible" model the adapter wraps.
#pragma once
#include <memory>

#include "Observers.h"

class HeartModelInterface {
public:
    virtual ~HeartModelInterface() = default;
    virtual int getHeartRate() = 0;
    virtual void registerObserver(std::shared_ptr<BeatObserver> o) = 0;
    virtual void removeObserver(std::shared_ptr<BeatObserver> o) = 0;
    virtual void registerObserver(std::shared_ptr<BPMObserver> o) = 0;
    virtual void removeObserver(std::shared_ptr<BPMObserver> o) = 0;
    // Simulation hook replacing the Java model's own thread.
    virtual void advance(int /*ms*/) {}
};
