# Chapter 3 – Decorator Pattern

**Intent:** attach additional responsibilities to an object dynamically. Decorators provide a flexible alternative to subclassing for extending functionality.

**Design principles from the chapter**
- Classes should be open for extension but closed for modification (Open-Closed Principle).
- (Reinforced) Favor composition over inheritance.

## Structure

```
Beverage (component) ◀── HouseBlend / DarkRoast / Decaf / Expresso     (concrete components)
   ▲
CondimentDecorator ──has-a──▶ Beverage ◀── Mocha / Soy / Whip           (decorators)

InputStream ◀── FileInputStream
   ▲
FilterInputStream ──has-a──▶ InputStream ◀── LowerCaseInputStream       (the java.io example)
```

A decorator is-a `Beverage` and has-a `Beverage`, so `new Whip(new Mocha(new Expresso()))` can be used anywhere a `Beverage` is expected. `cost()` and `getDescription()` delegate inward and add their own part. This repo's `Beverage` also has a `Size` that decorators forward to the wrapped drink (`Soy` prices by size).

## Layout and how to run

| Language | Folder    | Run |
|----------|-----------|-----|
| Java     | `java/`   | `javac -d out *.java && java -cp out StarbuzzCoffee` (and `InputTest`, run from `java/` because it reads `test.txt`) |
| Python   | `python/` | `python3 starbuzz_coffee.py` and `python3 input_test.py` (or `PYTHONPATH=. python3 ...`) |
| C++      | `cpp/`    | `make run` (C++17); builds `StarbuzzCoffee` and `InputTest` into `build/` |

`test.txt` is copied into `python/` and `cpp/` because `InputTest` opens it relative to the current directory; run from those folders.

## Java vs Python vs C++ in this chapter

| Topic | Java | Python | C++ |
|-------|------|--------|-----|
| Component interface | abstract class `Beverage` | `abc.ABC` with `@abstractmethod` | abstract class with pure virtuals |
| Wrapping | decorator holds a `Beverage` reference | same | `std::unique_ptr<Beverage>`: the decorator owns the wrapped object, so destroying the outer drink frees the whole chain |
| Stacking in `main` | `beverage2 = new Mocha(beverage2)` | `beverage2 = Mocha(beverage2)` | `beverage2 = std::make_unique<Mocha>(std::move(beverage2))` (ownership moves into the new decorator) |
| Constructors | each decorator repeats `this.beverage = beverage` | base `__init__` stores it | `using CondimentDecorator::CondimentDecorator;` inherits the constructor |
| Redundant overrides | every class re-declares `hasMilk()` etc. | shared in a base class | shared in `PlainBeverage` / `CondimentDecorator` |
| `java.io` decorator | `FilterInputStream` from the JDK | small `FilterInputStream` stand-in over a binary file object | hand-written `InputStream` / `FilterInputStream` / `FileInputStream`; `std::istream` has no decorator hierarchy |
| Double printing | `Double.toString` (shortest round-trip) | `repr` / f-string (same) | `<<` prints 6 digits, so a `formatDouble` helper finds the shortest round-tripping form |
| Java `size` field | package-private field | public attribute | `protected` member |

## Deviations and verification

- `InputTest` uses a Python/C++ re-implementation of `FilterInputStream` because those libraries have no equivalent; behavior (lower-casing each byte read) is the same. Both `read()` and the buffer overload are implemented, though `InputTest` only calls the single-byte one.
- Compiled the Java in a scratch directory and diffed stdout. `StarbuzzCoffee`: Python and C++ match exactly (including `2.5900000000000003`). `InputTest`: Python and C++ match exactly (byte-for-byte, no trailing newline). C++ builds with zero warnings under `-std=c++17 -Wall -Wextra -pedantic`.
