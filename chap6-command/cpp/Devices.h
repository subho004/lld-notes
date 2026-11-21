// Receivers: plain classes that do the real work and know nothing about commands.
#pragma once
#include <iostream>
#include <string>
#include <utility>

// Receivers: the objects that actually do the work.

class Light {
    std::string location;

public:
    explicit Light(std::string location = "") : location(std::move(location)) {}
    void on() { std::cout << location << " Light is on\n"; }
    void off() { std::cout << location << " Light is off\n"; }
};

class CeilingFan {
    std::string location;

public:
    explicit CeilingFan(std::string location) : location(std::move(location)) {}
    void on() { std::cout << location << " ceiling fan is on\n"; }
    void off() { std::cout << location << " ceiling fan is off\n"; }
};

// Receiver with speed state (name misspelling kept from the original repo).
class CelingFanv2 {
    std::string location;
    int speed = OFF;  // OFF is declared below; fine inside a class body

public:
    // static constexpr: compile-time constants, the C++ form of Java static final int.
    static constexpr int HIGH = 3;
    static constexpr int MEDIUM = 2;
    static constexpr int LOW = 1;
    static constexpr int OFF = 0;

    explicit CelingFanv2(std::string location) : location(std::move(location)) {}
    void high() { speed = HIGH; std::cout << location << " ceiling fan is on high\n"; }
    void medium() { speed = MEDIUM; std::cout << location << " ceiling fan is on medium\n"; }
    void low() { speed = LOW; std::cout << location << " ceiling fan is on low\n"; }
    void off() { speed = OFF; std::cout << location << " ceiling fan is off\n"; }
    int getSpeed() const { return speed; }
};

class Stereo {
    std::string location;

public:
    explicit Stereo(std::string location = "") : location(std::move(location)) {}
    void on() { std::cout << location << " Stereo is on\n"; }
    void off() { std::cout << location << " Stereo is off\n"; }
    void setCD() { std::cout << location << " Stereo is set for CD input\n"; }
    void setDVD() { std::cout << location << " Stereo is set for DVD input\n"; }
    void setRadio() { std::cout << location << " Stereo is set for radio input\n"; }
    void setVolume(int volume) { std::cout << location << " Stereo volume is set to " << volume << "\n"; }
};

class GarageDoor {
    std::string location;

public:
    explicit GarageDoor(std::string location = "") : location(std::move(location)) {}
    void up() { std::cout << location << " Garage Door is Open\n"; }
    void down() { std::cout << location << " Garage Door is Closed\n"; }
    void stop() { std::cout << location << " Garage Door is Stopped\n"; }
    void lightOn() { std::cout << location << " Garage Door light is on\n"; }
    void lightOff() { std::cout << location << " Garage Door light is off\n"; }
};
