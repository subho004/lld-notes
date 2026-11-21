// Concrete Subject (Model): BeatModel, notifying beat and BPM observers.
#pragma once
#include <iostream>
#include <memory>

#include "BeatModelInterface.h"
#include "ObserverList.h"

// Simulated beat clock: no thread, no sleep, no audio.  advance(ms) moves a
// virtual clock forward and fires every beat due strictly before the new time.
class BeatModel : public BeatModelInterface {
    // Observers are held weakly (see ObserverList.h).
    ObserverList<BeatObserver> beatObservers;
    ObserverList<BPMObserver> bpmObservers;
    int bpm = 90;
    bool stop = false;
    bool running = false;
    long now = 0;
    long nextBeatAt = 0;

    // 60000 / bpm plus 1 ms of simulated scheduling overhead, so a beat that
    // would land exactly on a boundary behaves like the real thread.
    int sleepMs() { return 60000 / getBPM() + 1; }

public:
    void initialize() override { std::cout << "clap.wav not found; running without audio" << std::endl; }

    void on() override {
        bpm = 90;
        notifyBPMObservers();
        stop = false;
        running = true;
        nextBeatAt = now;  // the Java thread beats immediately
    }

    void off() override {
        stopBeat();
        stop = true;
        running = false;
    }

    void advance(int ms) override {
        long target = now + ms;
        while (running && !stop && nextBeatAt < target) {
            now = nextBeatAt;
            playBeat();
            notifyBeatObservers();  // Observer: push each beat to the views
            nextBeatAt = now + sleepMs();
        }
        now = target;
    }

    void setBPM(int newBpm) override {
        bpm = newBpm;
        notifyBPMObservers();
    }

    int getBPM() override { return bpm; }

    // Overloads on observer type mirror the Java interface (Python renames them).
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

    void playBeat() {}  // no audio in the console port
    void stopBeat() {}
};
