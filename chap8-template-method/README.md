# Chapter 8 – Template Method Pattern

**Intent:** define the skeleton of an algorithm in a method, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps without changing the algorithm's structure.

**Design principle from the chapter**
- The Hollywood Principle: "Don't call us, we'll call you." High-level components (the base class) decide when to call low-level components (the subclasses), not the other way round.

## Structure

```
CaffieneBeverage            prepareRecipe() { boilWater(); brew(); pourInCup(); addCondiments(); }   <- template method (final)
   ├─ Coffee / Tea          implement brew(), addCondiments()

CaffeineBeverageWithHook    same, but: if (customerWantsCondiments()) addCondiments();              <- hook, default true
   ├─ CoffeeWithHook / TeaWithHook   override the hook to ask the user (stdin)

Duck implements Comparable  <- Arrays.sort() is a template method that calls compareTo()
MyStringList extends AbstractList  <- subList()/iteration are built on get()/size()
MyFrame extends JFrame      <- paint() is a hook the toolkit calls
```

Note: the Java file/class is spelled `CaffieneBeverage` (typo in the repo). The ports keep that spelling.

## Layout and how to run

| Language | Folder    | Run |
|----------|-----------|-----|
| Java     | `java/`   | `javac -d out *.java && java -cp out Coffee` (also `Tea`, `CoffeeWithHook`, `BeverageTestDrive`, `DuckSortTestDrive`, `MyStringListTestDrive`; `MyFrame` needs a display) |
| Python   | `python/` | `python3 coffee.py`, `tea.py`, `coffee_with_hook.py`, `beverage_test_drive.py`, `duck_sort_test_drive.py`, `my_string_list_test_drive.py`, `my_frame.py` |
| C++      | `cpp/`    | `make run` (builds all 7 programs; the hook ones read stdin), or `make && build/BeverageTestDrive` |

Interactive programs (`CoffeeWithHook`, `BeverageTestDrive`) read answers from stdin, e.g. `printf 'y\nn\n' | python3 beverage_test_drive.py`.

## Java vs Python vs C++ in this chapter

| Topic | Java | Python | C++ |
|-------|------|--------|-----|
| Template method that must not be overridden | `final void prepareRecipe()` | `@typing.final` (checked only by type checkers) | non-virtual public member function |
| Steps / hooks | package-private `abstract` / overridable methods | `@abstractmethod` + plain methods | `protected` pure/regular `virtual` methods: subclasses override, callers cannot call them directly |
| Abstract base | `abstract class` | `abc.ABC` (cannot be instantiated while abstract methods remain) | class with a pure virtual method + `virtual ~X() = default` |
| Override checking | `@Override` | none | `override` keyword |
| `Comparable<Duck>` + `Arrays.sort` | `compareTo`, stable merge/TimSort | `__lt__` (+`total_ordering`), `list.sort()` stable | `operator<`, `std::stable_sort` (plain `std::sort` is not stable and could reorder equal-weight ducks) |
| `AbstractList<String>` | inherit, implement `get`/`size`/`set`; `subList` and iteration come free | small generic `AbstractList` ABC with the same contract | small `AbstractList<T>` class template; `subList` returns a `unique_ptr` view that holds a raw pointer to its parent, so the parent must outlive it (Java's GC makes that automatic) |
| Iteration | `Iterable` | `__iter__` generator | `begin()/end()` with a small iterator class so range-for works |
| Reading input | new `BufferedReader` per question | shared `sys.stdin.readline()` | shared `std::getline(std::cin, ...)` |
| GUI | Swing `JFrame.paint(Graphics)` | headless `Frame`/`Graphics` classes | headless `Frame`/`Graphics` classes |

## Deviations and notes

- `MyFrame` is simulated: no Swing, no tkinter. A tiny `Frame` plays `JFrame`, `Graphics.drawString` prints its arguments, and `setVisible(true)` calls `paint()` the way the toolkit would. Python and C++ print identical text; Java opens a window (compiled only, not run).
- Java quirk: each question creates a new `BufferedReader` on `System.in`. When stdin is fully piped, the first reader swallows all input and the second `readLine()` returns `null`, causing a `NullPointerException` in `customerWantsCondiments`. For verification the Java input was fed with a delay between lines (`(echo y; sleep 1; echo n) | java ...`). The ports use one shared stdin stream so piped input works, and treat EOF as an empty answer (= "no").
- Output printed after a prompt is on the same line as the prompt in all three languages (no newline when stdin is piped).

## Verification

Java compiled into a scratch dir; every entry point's stdout was diffed against Java: `Coffee`, `Tea`, `CoffeeWithHook` and `BeverageTestDrive` (input `y` then `n`), `DuckSortTestDrive`, `MyStringListTestDrive` — all byte-identical for Python and C++. C++ builds with `-std=c++17 -Wall -Wextra -pedantic` and zero warnings. `MyFrame` is not comparable (GUI, see above). Build output was cleaned.
