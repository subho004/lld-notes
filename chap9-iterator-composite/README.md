# Chapter 9 – Iterator and Composite Patterns

**Iterator intent:** provide a way to access the elements of an aggregate sequentially without exposing its underlying representation.

**Composite intent:** compose objects into tree structures to represent part-whole hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly.

**Design principles from the chapter**
- A class should have only one reason to change (Single Responsibility): traversal is moved out of the aggregate and into an Iterator.
- Encapsulate what varies: the way each menu stores its items (ArrayList, array, HashMap) is hidden behind `Iterator`.
- Program to an interface: the Waitress depends on `Menu` and `Iterator`, not on concrete menus.
- (Composite) Trades some Single Responsibility for transparency: `MenuComponent` exposes both leaf and node operations, so clients treat both uniformly.

## Structure

```
Iterator:   Waitress ──▶ Menu.createIterator() ──▶ Iterator {hasNext, next}
            Menu:     PancakeHouseMenu (list)  ─▶ PancakeHouseIterator
                      DinnerMenu (array)       ─▶ DinerMenuIterator / AlternatingDinerMenuIterator
                      CafeMenu (hash map)      ─▶ CafeMenuIterator

Composite:  MenuComponent {add, remove, getChild, getName, ..., print}
              ├── MenuItem2   (leaf: print() prints itself)
              └── Menu2       (node: holds MenuComponents, print() recurses)
            Waitress2 ──▶ allMenus.print()
```

Java's `MenuTestDrive` uses the Iterator version (`Waitress`, `Menu`, `MenuItem`); `MenuTestDrive2` uses the Composite version (`Waitress2`, `MenuComponent`, `Menu2`, `MenuItem2`).

## Layout and how to run

| Language | Folder    | Entry points | Run |
|----------|-----------|--------------|-----|
| Java     | `java/`   | `MenuTestDrive`, `MenuTestDrive2` | `javac -d out *.java && java -cp out MenuTestDrive` |
| Python   | `python/` | `menu_test_drive.py`, `menu_test_drive2.py`, extra `native_iteration_demo.py` | `cd python && python3 menu_test_drive.py` (or `PYTHONPATH=. python3 ...`) |
| C++      | `cpp/`    | `MenuTestDrive.cpp`, `MenuTestDrive2.cpp`, extra `StlIterationDemo.cpp` | `cd cpp && make run` (C++17) |

There are no Java sub-folders. Python modules: `menu_item`, `iterator`, `menu`, `waitress`, `menu_component`, `waitress2`, `java_hash_order`. C++ headers: `MenuItem.h`, `Iterator.h`, `Iterators.h`, `Menu.h`, `Waitress.h`, `MenuComponent.h`, `Waitress2.h`, `JavaHashOrder.h`.

## Java vs Python vs C++ in this chapter

| Topic | Java | Python | C++ |
|-------|------|--------|-----|
| Iterator interface | own `interface Iterator` (hasNext/next) | `abc.ABC` `Iterator`, which also defines `__iter__`/`__next__` so book iterators work in `for` loops | abstract class `Iterator` with pure virtuals; plus STL-style `begin()`/`end()` on the menus |
| Native iteration | `java.util.Iterator` / `Iterable` (CafeMenuIterator wraps one) | iterator protocol; `Menu.__iter__` makes `for item in menu` work. A generator would replace each iterator class | range-for needs `begin()/end()` returning a type with `*`, `++`, `!=`; works with `<algorithm>` (`min_element`, `distance`) |
| End of iteration | `hasNext()` then `next()` | `StopIteration` raised by `__next__` | compare with `end()`; book-style uses `hasNext()` |
| Array with empty slots | `MenuItem[]` with `null` | `list` with `None` | `std::array<shared_ptr<MenuItem>, 6>` with `nullptr` |
| Iterator lifetime | iterator holds a GC reference to the collection | same | iterators hold a non-owning pointer into the menu, so the menu must outlive them; `createIterator()` returns `unique_ptr<Iterator>` (caller owns it) |
| Items | GC objects | GC objects | `shared_ptr<MenuItem>`, since menus and iterator callers share items |
| Composite ownership | parent holds references | parent holds references | `Menu2` owns children through `shared_ptr<MenuComponent>`; no cycles, as children have no parent pointer |
| "Unsupported" default methods | throw `UnsupportedOperationException` | raise `NotImplementedError` | throw a custom `UnsupportedOperationException` (derives `std::runtime_error`) |
| Generics | none used | type hints only | `DinerMenuIterator<N>` is a template over the fixed array size |
| HashMap order | `HashMap` order from `String.hashCode()` | dict is insertion-ordered | `unordered_map` order is unspecified |

## Deviations

- **CafeMenu order:** Java iterates a `HashMap`, so the order is defined by string hash codes. Python and C++ use `java_hash_order.py` / `JavaHashOrder.h` to reproduce Java's bucket order (String.hashCode, spread, table size 16 with resize) so output is identical.
- `Calendar.DAY_OF_WEEK` is the constant 7 in Java (not today's weekday); the Alternating iterators use `7 % 2`. They are not used by either test drive; `AlternatingDinerMenuIterator2` is an empty subclass in Python and omitted in C++ (identical to the first).
- Prices are printed with default formatting: Java `double`, Python `str(float)` and C++ `ostream` (6 significant digits) agree for these values.
- `remove()` on iterators is kept as a method that throws, but is not part of the `Iterator` interface (as in Java).

## Verification

Java was compiled in a scratch directory and both entry points were run. Python and C++ output of `MenuTestDrive` and `MenuTestDrive2` is byte-identical to Java's. The C++ build has zero warnings with `-std=c++17 -Wall -Wextra -pedantic`. `native_iteration_demo.py` and `StlIterationDemo` are additions with no Java counterpart.
