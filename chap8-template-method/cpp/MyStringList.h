// Concrete list over a vector<string>; supplies only get/size/set, the base provides the rest.
#pragma once
#include <string>
#include <vector>

#include "AbstractList.h"

// Owns its vector by value (moved in); subList views borrow from this object.
class MyStringList : public AbstractList<std::string> {
public:
    explicit MyStringList(std::vector<std::string> strings) : myList(std::move(strings)) {}

    std::string get(std::size_t index) const override { return myList.at(index); }
    std::size_t size() const override { return myList.size(); }
    std::string set(std::size_t index, const std::string& element) override {
        std::string oldString = myList.at(index);
        myList[index] = element;
        return oldString;
    }

private:
    std::vector<std::string> myList;
};
