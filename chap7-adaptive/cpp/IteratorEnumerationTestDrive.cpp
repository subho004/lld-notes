// Client: reads an ArrayList's Iterator through the IteratorEnumeration adapter.
#include <iostream>
#include <memory>
#include <string>

#include "IteratorEnumeration.h"
#include "JavaUtil.h"

int main() {
    ArrayList<std::string> list;
    list.add("Iterator");
    list.add("to");
    list.add("Enumeration");

    std::unique_ptr<Iterator<std::string>> iterator = list.iterator();
    // Ownership of the iterator moves into the adapter; "iterator" is empty afterwards.
    std::unique_ptr<Enumeration<std::string>> enumeration =
        std::make_unique<IteratorEnumeration<std::string>>(std::move(iterator));

    std::cout << "Iterating with IteratorEnumeration:\n";
    while (enumeration->hasMoreElements()) {
        std::cout << enumeration->nextElement() << "\n";
    }
    return 0;
}
