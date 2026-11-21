#pragma once
// Injectable random source for the WinnerState draw (Java: java.util.Random).
// Default is deterministic (never a winner) so output is reproducible.
//   GUMBALL_RANDOM=1   -> truly random (time-seeded), like the Java original
//   GUMBALL_SEED=<int> -> reproducible pseudo-random sequence (mt19937)
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <random>

// Strategy-like interface for the winner draw; header-only so it needs no extra build step.
class RandomSource {
public:
    // Virtual destructor: sources are owned and deleted through shared_ptr<RandomSource>.
    virtual ~RandomSource() = default;
    virtual int nextInt(int bound) = 0;  // returns value in [0, bound)
};

class FixedRandom : public RandomSource {
public:
    explicit FixedRandom(int value = 1) : value(value) {}
    int nextInt(int bound) override { return value % bound; }

private:
    int value;
};

class PseudoRandom : public RandomSource {
public:
    explicit PseudoRandom(unsigned long seed) : rng(static_cast<std::mt19937::result_type>(seed)) {}
    int nextInt(int bound) override {
        return std::uniform_int_distribution<int>(0, bound - 1)(rng);
    }

private:
    std::mt19937 rng;
};

// Picks the source from env vars: GUMBALL_RANDOM, then GUMBALL_SEED, else deterministic.
// inline so the header can be included from several translation units.
inline std::shared_ptr<RandomSource> defaultRandomSource() {
    const char* random = std::getenv("GUMBALL_RANDOM");
    if (random != nullptr && std::strcmp(random, "1") == 0) {
        auto now = std::chrono::system_clock::now().time_since_epoch();
        return std::make_shared<PseudoRandom>(static_cast<unsigned long>(
            std::chrono::duration_cast<std::chrono::milliseconds>(now).count()));
    }
    const char* seed = std::getenv("GUMBALL_SEED");
    if (seed != nullptr) return std::make_shared<PseudoRandom>(std::strtoul(seed, nullptr, 10));
    return std::make_shared<FixedRandom>(1);
}
