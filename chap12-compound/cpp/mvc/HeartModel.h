// Concrete Subject: HeartModel, the model that HeartAdapter adapts for the view.
#pragma once
#include <cstdint>

#include "HeartModelInterface.h"
#include "ObserverList.h"

// Small deterministic LCG (same constants as the Python port) replacing
// java.util.Random(System.currentTimeMillis()).
class SimRandom {
    std::uint64_t state;

public:
    explicit SimRandom(std::uint64_t seed) : state(seed & 0x7FFFFFFF) {}
    int nextInt(int bound) {
        state = (state * 1103515245ULL + 12345ULL) & 0x7FFFFFFF;
        return static_cast<int>((state >> 16) % static_cast<std::uint64_t>(bound));
    }
};

// Simulated heart with a fixed-seed generator, so output is reproducible.
class HeartModel : public HeartModelInterface {
    ObserverList<BeatObserver> beatObservers;
    ObserverList<BPMObserver> bpmObservers;
    int time = 1000;
    SimRandom random;
    int lastrate = -1;
    long now = 0;
    long nextIterationAt = 0;

    // Body of Java's `while (true)` loop (minus the sleep).
    void runOnce() {
        int change = random.nextInt(10);
        if (random.nextInt(2) == 0) {
            change = 0 - change;
        }
        int rate = 60000 / (time + change);
        // Accept the change only when the new rate stays in a plausible range.
        if (rate < 120 && rate > 50) {
            time += change;
            notifyBeatObservers();
            if (rate != lastrate) {  // BPM observers hear only about real changes
                lastrate = rate;
                notifyBPMObservers();
            }
        }
    }

public:
    explicit HeartModel(std::uint64_t seed = 42) : random(seed) {}

    // Thread.sleep(time) becomes nextIterationAt.
    void advance(int ms) override {
        long target = now + ms;
        while (nextIterationAt < target) {
            now = nextIterationAt;
            runOnce();
            nextIterationAt = now + time;
        }
        now = target;
    }

    int getHeartRate() override { return 60000 / time; }

    void registerObserver(std::shared_ptr<BeatObserver> o) override { beatObservers.add(o); }
    void removeObserver(std::shared_ptr<BeatObserver> o) override { beatObservers.remove(o); }
    void registerObserver(std::shared_ptr<BPMObserver> o) override { bpmObservers.add(o); }
    void removeObserver(std::shared_ptr<BPMObserver> o) override { bpmObservers.remove(o); }

    void notifyBeatObservers() {
        beatObservers.notify([](BeatObserver& o) { o.updateBeat(); });
    }
    void notifyBPMObservers() {
        bpmObservers.notify([](BPMObserver& o) { o.updateBPM(); });
    }
};
