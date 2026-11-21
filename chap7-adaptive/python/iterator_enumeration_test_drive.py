"""Client: reads an ArrayList's Iterator through the IteratorEnumeration adapter."""
from iterator_enumeration import IteratorEnumeration
from java_util import ArrayList, Enumeration


def main() -> None:
    items: ArrayList[str] = ArrayList()
    items.add("Iterator")
    items.add("to")
    items.add("Enumeration")

    iterator = items.iterator()
    enumeration: Enumeration[str] = IteratorEnumeration(iterator)

    print("Iterating with IteratorEnumeration:")
    while enumeration.has_more_elements():
        print(enumeration.next_element())


if __name__ == "__main__":
    main()
