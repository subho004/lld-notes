// Part of the View: the beat bar (header-only; replaces Swing JProgressBar).
#pragma once
#include <string>

// JProgressBar + Thread in Java; here step() is one 50 ms tick of the decay
// loop (value = (int)(value * .75)), called by DJView::tick().
class BeatBar {
    int maximum = 100;
    int value = 0;

public:
    void setValue(int v) { value = v; }
    int getValue() const { return value; }
    void step() { value = static_cast<int>(value * 0.75); }
    std::string render() const {
        // Text stands in for painting: 10 cells, one per 10 points.
        int filled = value / 10;
        return "|" + std::string(filled, '#') + std::string(10 - filled, '.') + "|";
    }
    int getMaximum() const { return maximum; }
};
