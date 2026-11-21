// Subject interface for the protection proxy; implemented by PersonImpl
// (real) and PersonProxy (stand-in).
#pragma once
#include <string>

// Subject. Virtual destructor so shared_ptr<Person> deletes correctly.
class Person {
public:
    virtual ~Person() = default;
    virtual std::string getName() = 0;
    virtual std::string getGender() = 0;
    virtual std::string getInterests() = 0;
    virtual int getGeekRating() = 0;
    virtual void setName(const std::string& name) = 0;
    virtual void setGender(const std::string& gender) = 0;
    virtual void setInterests(const std::string& interests) = 0;
    virtual void setGeekRating(int rating) = 0;
};
