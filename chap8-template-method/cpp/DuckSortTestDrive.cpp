// Client: sorts Ducks via Duck::operator<, the hook the sort algorithm calls back.
#include <algorithm>
#include <iostream>
#include <vector>

#include "Duck.h"

void printDucks(const std::vector<Duck>& ducks) {
    for (const Duck& duck : ducks) {
        std::cout << duck.toString() << "\n";
    }
}

int main() {
    std::vector<Duck> ducks = {
        Duck("Daffy", 8),   Duck("Dewey", 2), Duck("Howard", 7),
        Duck("Louie", 2),   Duck("Donald", 10), Duck("Huey", 2),
    };
    std::cout << "Before sorting:\n";
    printDucks(ducks);
    // stable_sort, not sort: equal-weight ducks must keep their order, as in Java.
    std::stable_sort(ducks.begin(), ducks.end());  // Arrays.sort on objects is stable
    std::cout << "\nAfter sorting:\n";
    printDucks(ducks);
}
