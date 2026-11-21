// Strategy interface: what the view may ask a controller to do.
#pragma once

// The view depends only on this, never on a concrete controller.
class ControllerInterface {
public:
    virtual ~ControllerInterface() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void increaseBPM() = 0;
    virtual void decreaseBPM() = 0;
    virtual void setBPM(int bpm) = 0;
};
