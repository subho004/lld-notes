"""Client: iterates a Vector's Enumeration through the EnumerationIterator adapter."""
from enumeration_iterator import EnumerationIterator
from java_util import Iterator, Vector


def main() -> None:
    vector: Vector[str] = Vector()
    vector.add("Java")
    vector.add("Adapter")
    vector.add("Pattern")

    enumeration = vector.elements()
    iterator: Iterator[str] = EnumerationIterator(enumeration)

    print("Iterating with EnumerationIterator:")
    while iterator.has_next():
        print(iterator.next())


if __name__ == "__main__":
    main()
