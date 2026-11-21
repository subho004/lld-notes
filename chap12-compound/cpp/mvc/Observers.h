// Observer interfaces for the model, plus std::function-based wrappers.
#pragma once
#include <functional>
#include <utility>

// Observer interface: notified on every beat.
class BeatObserver {
public:
    virtual ~BeatObserver() = default;
    virtual void updateBeat() = 0;
};

// Observer interface: notified when the BPM changes.
class BPMObserver {
public:
    virtual ~BPMObserver() = default;
    virtual void updateBPM() = 0;
};

// Stand-ins for Java's lambda-as-observer; shared_ptr identity needs a real class.
class FunctionBeatObserver : public BeatObserver {
    std::function<void()> fn;

public:
    explicit FunctionBeatObserver(std::function<void()> fn) : fn(std::move(fn)) {}
    void updateBeat() override { fn(); }
};

class FunctionBPMObserver : public BPMObserver {
    std::function<void()> fn;

public:
    explicit FunctionBPMObserver(std::function<void()> fn) : fn(std::move(fn)) {}
    void updateBPM() override { fn(); }
};
