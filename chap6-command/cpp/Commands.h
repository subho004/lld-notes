// Concrete Commands: each binds a receiver (Light, Stereo, ...) to an action and its undo.
#pragma once
#include <memory>

#include "Command.h"
#include "Devices.h"

// Concrete commands. Receivers are shared (shared_ptr) because the same Light etc.
// is referenced by several commands and by main().

class LightOnCommand : public Command {
    std::shared_ptr<Light> light;

public:
    explicit LightOnCommand(std::shared_ptr<Light> light) : light(std::move(light)) {}
    void execute() override { light->on(); }
    void undo() override { light->off(); }
    std::string name() const override { return "LightOnCommand"; }
};

class LightOffCommand : public Command {
    std::shared_ptr<Light> light;

public:
    explicit LightOffCommand(std::shared_ptr<Light> light) : light(std::move(light)) {}
    void execute() override { light->off(); }
    void undo() override { light->on(); }
    std::string name() const override { return "LightOffCommand"; }
};

class CeilingFanOnCommand : public Command {
    std::shared_ptr<CeilingFan> ceilingFan;

public:
    explicit CeilingFanOnCommand(std::shared_ptr<CeilingFan> f) : ceilingFan(std::move(f)) {}
    void execute() override { ceilingFan->on(); }
    void undo() override { ceilingFan->off(); }
    std::string name() const override { return "CeilingFanOnCommand"; }
};

class CeilingFanOffCommand : public Command {
    std::shared_ptr<CeilingFan> ceilingFan;

public:
    explicit CeilingFanOffCommand(std::shared_ptr<CeilingFan> f) : ceilingFan(std::move(f)) {}
    void execute() override { ceilingFan->off(); }
    void undo() override { ceilingFan->on(); }
    std::string name() const override { return "CeilingFanOffCommand"; }
};

// Shared "remember previous speed and restore it on undo" logic (repeated in each Java class).
// Abstract: execute() is left to subclasses, so this class stays abstract.
class CeilingFanSpeedCommand : public Command {
protected:
    std::shared_ptr<CelingFanv2> ceilingFan;
    int prevSpeed = 0;

public:
    explicit CeilingFanSpeedCommand(std::shared_ptr<CelingFanv2> f) : ceilingFan(std::move(f)) {}
    void undo() override {
        if (prevSpeed == CelingFanv2::HIGH) {
            ceilingFan->high();
        } else if (prevSpeed == CelingFanv2::MEDIUM) {
            ceilingFan->medium();
        } else if (prevSpeed == CelingFanv2::LOW) {
            ceilingFan->low();
        } else {
            ceilingFan->off();
        }
    }
};

class CeilingFanHighCommand : public CeilingFanSpeedCommand {
public:
    using CeilingFanSpeedCommand::CeilingFanSpeedCommand;  // inherit the base constructor
    // Save the current speed first so undo() can restore it.
    void execute() override { prevSpeed = ceilingFan->getSpeed(); ceilingFan->high(); }
    std::string name() const override { return "CeilingFanHighCommand"; }
};

class CeilingFanMediumCommand : public CeilingFanSpeedCommand {
public:
    using CeilingFanSpeedCommand::CeilingFanSpeedCommand;
    void execute() override { prevSpeed = ceilingFan->getSpeed(); ceilingFan->medium(); }
    std::string name() const override { return "CeilingFanMediumCommand"; }
};

class CeilingFanLowCommand : public CeilingFanSpeedCommand {
public:
    using CeilingFanSpeedCommand::CeilingFanSpeedCommand;
    void execute() override { prevSpeed = ceilingFan->getSpeed(); ceilingFan->low(); }
    std::string name() const override { return "CeilingFanLowCommand"; }
};

class CeilingFanv2OffCommand : public CeilingFanSpeedCommand {
public:
    using CeilingFanSpeedCommand::CeilingFanSpeedCommand;
    void execute() override { prevSpeed = ceilingFan->getSpeed(); ceilingFan->off(); }
    std::string name() const override { return "CeilingFanv2OffCommand"; }
};

class GarageDoorOpenCommand : public Command {
    std::shared_ptr<GarageDoor> garageDoor;

public:
    explicit GarageDoorOpenCommand(std::shared_ptr<GarageDoor> g) : garageDoor(std::move(g)) {}
    void execute() override { garageDoor->up(); }
    void undo() override { garageDoor->down(); }
    std::string name() const override { return "GarageDoorOpenCommand"; }
};

// Duplicate of GarageDoorOpenCommand, kept separate to mirror the Java (name() differs).
class GarageDoorUpCommand : public Command {
    std::shared_ptr<GarageDoor> garageDoor;

public:
    explicit GarageDoorUpCommand(std::shared_ptr<GarageDoor> g) : garageDoor(std::move(g)) {}
    void execute() override { garageDoor->up(); }
    void undo() override { garageDoor->down(); }
    std::string name() const override { return "GarageDoorUpCommand"; }
};

class GarageDoorDownCommand : public Command {
    std::shared_ptr<GarageDoor> garageDoor;

public:
    explicit GarageDoorDownCommand(std::shared_ptr<GarageDoor> g) : garageDoor(std::move(g)) {}
    void execute() override { garageDoor->down(); }
    void undo() override { garageDoor->up(); }
    std::string name() const override { return "GarageDoorDownCommand"; }
};

class StereoOnWithCDCommand : public Command {
    std::shared_ptr<Stereo> stereo;

public:
    explicit StereoOnWithCDCommand(std::shared_ptr<Stereo> s) : stereo(std::move(s)) {}
    void execute() override {
        // One command driving several receiver calls.
        stereo->on();
        stereo->setCD();
        stereo->setVolume(11);
    }
    void undo() override { stereo->off(); }
    std::string name() const override { return "StereoOnWithCDCommand"; }
};

class StereoOffCommand : public Command {
    std::shared_ptr<Stereo> stereo;

public:
    explicit StereoOffCommand(std::shared_ptr<Stereo> s) : stereo(std::move(s)) {}
    void execute() override { stereo->off(); }
    void undo() override { stereo->on(); }
    std::string name() const override { return "StereoOffCommand"; }
};
