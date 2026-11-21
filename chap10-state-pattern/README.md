# Chapter 10 – State Pattern

**Intent:** allow an object to alter its behavior when its internal state changes. The object will appear to change its class.

**Design principles from the chapter**
- Encapsulate what varies: each state's behavior goes into its own class.
- Open/closed: add new states (like `WinnerState`) without rewriting the context's conditionals.
- Replace conditional logic with polymorphism and delegation to a state object.
- (Strategy vs State: both use composition and delegation. State changes itself as the context moves between states; Strategy is normally chosen once by the client.)

## Structure

```
GumballMachine2 (context) ──has-a current──▶ State  ◀── NoQuarterState / HasQuarterState
   insertQuarter() -> state.insertQuarter()            SoldState / SoldOutState / WinnerState
   setState(State)  ◀── states call back to switch the machine's state
```

`GumballMachine` (v1) is the "before" version: an int `state` and if/else in every method. `GumballMachine2` is the "after" version with `State` objects. The `TestDrive` programs exercise each one.

## Layout and how to run

| Language | Folder    | Run |
|----------|-----------|-----|
| Java     | `java/`   | `javac -d out *.java && java -cp out GumballMachineTestDrive` (and `GumballMachineTestDrive2`) |
| Python   | `python/` | `PYTHONPATH=. python3 gumball_machine_test_drive.py` / `gumball_machine_test_drive2.py` (plain `python3 file.py` also works from that folder) |
| C++      | `cpp/`    | `make run` (C++17). Binaries: `build/GumballMachineTestDrive`, `build/GumballMachineTestDrive2` |

There are no sub-folders in this chapter.

## Randomness (WinnerState)

Java's `HasQuarterState` draws `new Random(System.currentTimeMillis()).nextInt(10)`, so a 1-in-10 winner makes Java output non-reproducible. Python and C++ inject a `RandomSource` (`random_source.py` / `RandomSource.h`) into `GumballMachine2`, which passes it to `HasQuarterState`:

| Setting | Behavior |
|---------|----------|
| default | `FixedRandom(1)`: never a winner, output is deterministic |
| `GUMBALL_SEED=<n>` | reproducible pseudo-random sequence (Python `random.Random`, C++ `std::mt19937`; sequences differ between languages) |
| `GUMBALL_RANDOM=1` | time-seeded, truly random like Java |
| code | `GumballMachine2(5, my_random_source)` |

## Java vs Python vs C++ in this chapter

| Topic | Java | Python | C++ |
|-------|------|--------|-----|
| State interface | `interface State` | `abc.ABC` + `@abstractmethod` | class with pure virtuals, `virtual ~State() = default` |
| State <-> Context cycle | classes in separate files reference each other freely | `TYPE_CHECKING` import + `from __future__ import annotations` avoids a circular import | forward declaration `class GumballMachine2;` in state headers; method bodies in `StateImpl.h`, included after the context is complete |
| Who owns the states | GC | GC | context holds `std::unique_ptr<State>` for each; the current state is a raw non-owning `State*`; states keep a non-owning `GumballMachine2&` (no ownership cycle, so no leak); machine is non-copyable |
| `toString` of a state | default `Object.toString()` (`Name@hash`) | `__str__` mimics `Name@hex` | `dynamic_cast` name + address mimics it |
| Random | `java.util.Random` inline | injectable `RandomSource` | injectable `std::shared_ptr<RandomSource>` (shared with the state) |
| v1 constants | `static final int` | class attributes | `static constexpr int` |
| Override checking | `@Override` (not used here) | none | `override` |

## Deviations and verification

- Java's `GumballMachine2.toString()` prints the state's identity hash (e.g. `NoQuarterState@58644d46`). The hash differs per run and language, so Python/C++ print the same shape with their own id/address.
- Randomness is deterministic by default (see above).

Verification: Java, Python and C++ were run for both `GumballMachineTestDrive` and `GumballMachineTestDrive2`. Output is identical once the `@hash` suffix is normalized. The C++ build has zero warnings under `-Wall -Wextra -pedantic`. The seeded and random winner paths were exercised in Python and C++ (a "YOU'RE A WINNER" line appears); they were not compared against Java.
