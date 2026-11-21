// Duck: element type sorted by std::stable_sort, the C++ counterpart of Comparable<Duck>.
#pragma once
#include <string>

class Duck {
public:
    Duck(std::string name, int weight) : name(std::move(name)), weight(weight) {}

    std::string toString() const { return name + " weighs " + std::to_string(weight); }

    // Java-style three-way comparison by weight, kept for parity with the original.
    int compareTo(const Duck& otherDuck) const {
        if (weight < otherDuck.weight) return -1;
        if (weight > otherDuck.weight) return 1;
        return 0;
    }

    // Comparable<Duck> -> operator< so std::sort / std::stable_sort work.
    bool operator<(const Duck& other) const { return compareTo(other) < 0; }

    std::string name;
    int weight;
};
