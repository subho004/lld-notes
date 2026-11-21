// Adapter: HeartAdapter makes a HeartModel look like a BeatModelInterface.
#pragma once
#include <memory>

#include "BeatModelInterface.h"
#include "HeartModelInterface.h"

// Adapter: lets a HeartModel be used where a BeatModel is expected.
class HeartAdapter : public BeatModelInterface {
    std::shared_ptr<HeartModelInterface> heart;

public:
    explicit HeartAdapter(std::shared_ptr<HeartModelInterface> h) : heart(std::move(h)) {}

    // Controls that make no sense for a heart are deliberately no-ops.
    void initialize() override {}
    void on() override {}
    void off() override {}
    // Translate: a heart rate is the BPM.
    int getBPM() override { return heart->getHeartRate(); }
    void setBPM(int) override {}

    // Observer calls are forwarded to the adaptee.
    void registerObserver(std::shared_ptr<BeatObserver> o) override { heart->registerObserver(o); }
    void removeObserver(std::shared_ptr<BeatObserver> o) override { heart->removeObserver(o); }
    void registerObserver(std::shared_ptr<BPMObserver> o) override { heart->registerObserver(o); }
    void removeObserver(std::shared_ptr<BPMObserver> o) override { heart->removeObserver(o); }

    void advance(int ms) override { heart->advance(ms); }
};
