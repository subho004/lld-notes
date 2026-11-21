// Client: iterates a MyStringList and a sub-list view, both using inherited template methods.
#include <iostream>
#include <string>
#include <vector>

#include "MyStringList.h"

int main() {
    std::vector<std::string> ducks = {"Mallard Duck", "Redhead Duck", "Rubber Duck", "Decoy Duck"};
    MyStringList ducksList(ducks);
    // View, not a copy; ducksList must stay alive while it is used.
    auto ducksSubList = ducksList.subList(2, 3);

    std::cout << "Full list:\n";
    for (const std::string& duck : ducksList) {
        std::cout << duck << "\n";
    }

    std::cout << "\nSublist (index 2, one item):\n";
    for (const std::string& duck : *ducksSubList) {
        std::cout << duck << "\n";
    }
}
