// Model interface (Subject side of Observer) that views and controllers depend on.
#pragma once
#include <memory>

#include "Observers.h"

// Pure interface; virtual destructor allows deletion through a shared_ptr/base pointer.
class BeatModelInterface {
public:
    virtual ~BeatModelInterface() = default;
    virtual void initialize() = 0;
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void setBPM(int bpm) = 0;
    virtual int getBPM() = 0;
    virtual void registerObserver(std::shared_ptr<BeatObserver> o) = 0;
    virtual void removeObserver(std::shared_ptr<BeatObserver> o) = 0;
    virtual void registerObserver(std::shared_ptr<BPMObserver> o) = 0;
    virtual void removeObserver(std::shared_ptr<BPMObserver> o) = 0;

    // Simulation hook (replaces the Java model's own thread + Thread.sleep).
    // Non-pure no-op so models without a clock need not override it.
    virtual void advance(int /*ms*/) {}
};
