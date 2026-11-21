// Console stand-ins for Swing: Graphics, Component, Icon (Subject interface),
// ImageIcon (Real Subject), SimulatedThread and Scheduler. Header-only.
#pragma once
// Console stand-ins for the Swing/AWT bits used by the virtual proxy demo.
// Thread is replaced by SimulatedThread + a Scheduler whose clock advances one
// tick per Scheduler::tick(), so "loading" is deterministic.
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Console replacement for java.awt.Graphics.
class Graphics {
public:
    void drawString(const std::string& text, int x, int y) {
        std::cout << "  [draw] string '" << text << "' at (" << x << "," << y << ")\n";
    }
};

// Base for paintable widgets; virtual repaint() lets ImageComponent override it.
class Component {
public:
    virtual ~Component() = default;
    virtual void repaint() { std::cout << "  [repaint requested]\n"; }
};

// Subject interface shared by ImageIcon and ImageProxy.
class Icon {
public:
    virtual ~Icon() = default;
    virtual int getIconWidth() = 0;
    virtual int getIconHeight() = 0;
    virtual void paintIcon(Component& c, Graphics& g, int x, int y) = 0;
};

// Fake ImageIcon: constructing it is the "slow download". Size is fixed.
class ImageIcon : public Icon {
    std::string url, description;

public:
    ImageIcon(std::string u, std::string d) : url(std::move(u)), description(std::move(d)) {}
    int getIconWidth() override { return 300; }
    int getIconHeight() override { return 300; }
    void paintIcon(Component&, Graphics&, int x, int y) override {
        std::cout << "  [draw] image '" << description << "' (" << url << ") at (" << x << "," << y << ")\n";
    }
};

// Deterministic replacement for java.lang.Thread; runs after delayTicks ticks.
class SimulatedThread {
public:
    std::function<void()> target;
    int remaining;
    explicit SimulatedThread(std::function<void()> t, int delayTicks = 2)
        : target(std::move(t)), remaining(delayTicks) {}
    void start();
};

// Singleton clock that runs queued SimulatedThreads as tick() is called.
class Scheduler {
    std::vector<std::shared_ptr<SimulatedThread>> pending;

public:
    static Scheduler& instance() {
        static Scheduler s;
        return s;
    }
    void add(std::shared_ptr<SimulatedThread> t) { pending.push_back(std::move(t)); }
    void tick() {
        // Iterate a copy: a thread's target may enqueue new threads while running.
        auto snapshot = pending;
        for (auto& t : snapshot) {
            if (--t->remaining <= 0) {
                for (auto it = pending.begin(); it != pending.end(); ++it) {
                    if (*it == t) {
                        pending.erase(it);
                        break;
                    }
                }
                t->target();
            }
        }
    }
};

// A started thread is owned by the scheduler until it has run.
// (Java's Thread object is also kept alive by the JVM while running.)

inline void SimulatedThread::start() {
    Scheduler::instance().add(std::make_shared<SimulatedThread>(*this));
}
