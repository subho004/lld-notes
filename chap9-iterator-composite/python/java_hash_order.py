"""Helper that reproduces java.util.HashMap iteration order for String keys.

Java's CafeMenu stores items in a HashMap, so its iteration order is decided by
String.hashCode(). Python dicts keep insertion order, so to print exactly what
the Java program prints we order entries by their HashMap bucket index.
(Entries in the same bucket keep insertion order; table resizing is modelled.)
"""
from typing import List, TypeVar

T = TypeVar("T")


# Java's String.hashCode(): s[0]*31^(n-1) + ... over UTF-16 code units, kept to 32 bits.
def java_string_hash(s: str) -> int:
    h = 0
    data = s.encode("utf-16-le")
    for i in range(0, len(data), 2):
        h = (31 * h + (data[i] | (data[i + 1] << 8))) & 0xFFFFFFFF
    return h


# HashMap spreads the hash (h ^ h>>>16) and masks it with the power-of-two table size.
def bucket_index(key: str, table_size: int) -> int:
    h = java_string_hash(key)
    return (h ^ (h >> 16)) & (table_size - 1)


def java_hashmap_order(keys: List[str], values: List[T]) -> List[T]:
    # Default capacity 16; doubles while size exceeds the 0.75 load factor.
    table = 16
    while len(keys) > table * 0.75:
        table *= 2
    # Sorting by (bucket, insertion index) approximates Java's bucket iteration order.
    order = sorted(range(len(keys)), key=lambda i: (bucket_index(keys[i], table), i))
    return [values[i] for i in order]
