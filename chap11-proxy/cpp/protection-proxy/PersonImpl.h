// PersonImpl: Real Subject. Plain data holder with no access checks;
// handlers decide who may call what.
#pragma once
#include <string>

#include "Person.h"

// Real Subject.
class PersonImpl : public Person {
    std::string name;
    std::string gender;
    std::string interests;
    int rating = 0;
    int ratingCount = 0;

public:
    std::string getName() override { return name; }
    std::string getGender() override { return gender; }
    std::string getInterests() override { return interests; }
    int getGeekRating() override {
        if (ratingCount == 0) return 0;
        // Integer average, as in Java.
        return rating / ratingCount;
    }
    void setName(const std::string& n) override { name = n; }
    void setGender(const std::string& g) override { gender = g; }
    void setInterests(const std::string& i) override { interests = i; }
    void setGeekRating(int r) override {
        rating += r;
        ratingCount++;
    }
};
