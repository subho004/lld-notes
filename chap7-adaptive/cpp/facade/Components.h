// Subsystem classes behind the facade; each only prints what the real device would do (header-only).
#pragma once
#include <iostream>
#include <string>
#include <utility>

// Defined first because Amplifier uses it. toString() is the Java toString().
class StreamingPlayer {
public:
    explicit StreamingPlayer(std::string description) : description(std::move(description)) {}
    void on() { std::cout << description << " player on\n"; }
    void off() { std::cout << description << " player off\n"; }
    void play(const std::string& movie) {
        std::cout << description << " player playing \"" << movie << "\"\n";
    }
    void stop() { std::cout << description << " player stopped\n"; }
    std::string toString() const { return description + " Streaming Player"; }

private:
    std::string description;
};

class Amplifier {
public:
    explicit Amplifier(std::string description) : description(std::move(description)) {}
    void on() { std::cout << description << " amplifier on\n"; }
    void off() { std::cout << description << " amplifier off\n"; }
    void setStreamingPlayer(const StreamingPlayer& player) {
        std::cout << description << " amplifier streaming player set to " << player.toString() << "\n";
    }
    void setVolume(int level) {
        std::cout << description << " amplifier volume set to " << level << "\n";
    }

private:
    std::string description;
};

// Keeps a reference to the amplifier (owned by main); the facade never uses the tuner.
class Tuner {
public:
    Tuner(std::string description, Amplifier& amplifier)
        : description(std::move(description)), amplifier(amplifier) {}
    void on() { std::cout << description << " tuner on\n"; }
    void off() { std::cout << description << " tuner off\n"; }
    void setAmFm() { std::cout << description << " tuner set to AM/FM mode\n"; }

private:
    std::string description;
    [[maybe_unused]] Amplifier& amplifier;  // stored but unused, as in Java; silences -Wextra
};

class Projector {
public:
    explicit Projector(std::string description) : description(std::move(description)) {}
    void on() { std::cout << description << " projector on\n"; }
    void off() { std::cout << description << " projector off\n"; }
    void wideScreenMode() {
        std::cout << description << " projector in widescreen mode (16x9 aspect ratio)\n";
    }

private:
    std::string description;
};

class TheaterLights {
public:
    explicit TheaterLights(std::string description) : description(std::move(description)) {}
    void on() { std::cout << description << " lights on\n"; }
    void off() { std::cout << description << " lights off\n"; }
    void dim(int level) { std::cout << description << " lights dimmed to " << level << "%\n"; }

private:
    std::string description;
};

class Screen {
public:
    explicit Screen(std::string description) : description(std::move(description)) {}
    void up() { std::cout << description << " screen going up\n"; }
    void down() { std::cout << description << " screen going down\n"; }

private:
    std::string description;
};

class PopcornPopper {
public:
    explicit PopcornPopper(std::string description) : description(std::move(description)) {}
    void on() { std::cout << description << " popper on\n"; }
    void off() { std::cout << description << " popper off\n"; }
    void pop() { std::cout << description << " popper popping popcorn!\n"; }

private:
    std::string description;
};
