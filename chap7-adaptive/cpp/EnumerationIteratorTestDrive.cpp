// Client: iterates a Vector's Enumeration through the EnumerationIterator adapter.
#include <iostream>
#include <memory>
#include <string>

#include "EnumerationIterator.h"
#include "JavaUtil.h"

int main() {
    Vector<std::string> vector;
    vector.add("Java");
    vector.add("Adapter");
    vector.add("Pattern");

    std::unique_ptr<Enumeration<std::string>> enumeration = vector.elements();
    // Ownership of the enumeration moves into the adapter; "enumeration" is empty afterwards.
    std::unique_ptr<Iterator<std::string>> iterator =
        std::make_unique<EnumerationIterator<std::string>>(std::move(enumeration));

    std::cout << "Iterating with EnumerationIterator:\n";
    while (iterator->hasNext()) {
        std::cout << iterator->next() << "\n";
    }
    return 0;
}
