# Chapter 12 – Compound Patterns

**Intent:** combine several patterns in one design so they work together to solve a problem. The chapter builds a duck simulator from Adapter, Decorator, Abstract Factory, Composite and Observer. It then looks at Model-View-Controller, which is itself a compound of Observer, Strategy and Composite, and shows the Adapter-to-Model trick that lets a `HeartModel` drive a `BeatModel` view.

**Design principles from the chapter**
- Patterns are often used together, but a compound pattern is a set of patterns that solves a recurring general problem (MVC is the example).
- Program to an interface, not an implementation (views, controllers and models only see `BeatModelInterface` / `ControllerInterface`).
- Favor composition over inheritance.
- Strive for loosely coupled designs between objects that interact (Observer keeps the model ignorant of its views).
- Encapsulate what varies (the factory hides which decorated duck is created).

## Structure

Duck simulator (`java/`):

```
Quackable (extends QuackObservable) <- MallardDuck, RedheadDuck, DuckCall, RubberDuck
   Adapter:   GooseAdapter  --wraps--> Goose
   Decorator: QuackCounter  --wraps--> Quackable
   Composite: Flock         --holds--> Quackable*   (a Flock is a Quackable)
   Factory:   AbstractDuckFactory <- DuckFactory, CountingDuckFactory (wraps ducks in QuackCounter)
   Observer:  Observable (helper owned by each duck) --notifies--> Observer <- Quackologist
```

MVC (`java/mvc/`):

```
DJView  --observes--> BeatModelInterface <- BeatModel      (real model)
   |                                      <- HeartAdapter -> HeartModelInterface <- HeartModel
   +--user input--> ControllerInterface <- BeatController / HeartController
BeatObserver.updateBeat()   BPMObserver.updateBPM()   (the Observer part)
```

The controller is the strategy for the view; the view is a composite of widgets; the model notifies observers.

## Layout and how to run

| Language | Folder | Run |
|----------|--------|-----|
| Java     | `java/` (duck simulator) | `javac -d out *.java && java -cp out DuckSimulator` |
| Java     | `java/mvc/` | `javac -d out *.java && java -cp out BeatModelTestDrive` (`DJTestDrive` and `HeartTestDrive` need a display) |
| Python   | `python/` | `python3 duck_simulator.py` |
| Python   | `python/mvc/` | `cd python/mvc && python3 beat_model_test_drive.py` (also `dj_test_drive.py`, `heart_test_drive.py`) |
| C++      | `cpp/` | `make run` (builds `DuckSimulator`) |
| C++      | `cpp/mvc/` | `cd cpp/mvc && make run` (builds `BeatModelTestDrive`, `DJTestDrive`, `HeartTestDrive`) |

## Simulation deviations (mvc)

The Java MVC code needs Swing, `javax.sound` and several threads (`BeatModel`, `HeartModel` and `BeatBar` each run a loop with `Thread.sleep`). The Python and C++ ports replace these:

- **Swing** becomes `swing_sim.py` / `SwingSim.h`: headless `Label`, `TextField`, `Button` and `MenuItem` with enabled flags and listeners. `click()` plays the user, and prints `[GUI] ...` lines. `DJView` keeps `createView`, `createControls`, `actionPerformed` and the observer callbacks, and adds `show()`, which prints one text line (`|###.......| Current BPM: 120`).
- **Sound** is dropped. `BeatModel.initialize()` prints the same "clap.wav not found; running without audio" line the Java code prints when no audio file exists.
- **Threads and sleeps** become a manual clock. `model.advance(ms)` runs every loop iteration due before the new time (`BeatModel`: beat, notify, then wait `60000/bpm`; `HeartModel`: the body of its `while(true)`, then wait `time`). `BeatBar.step()` is one 50 ms decay frame, called by `DJView.tick()`. Nothing sleeps, so runs are instant and deterministic.
- `BeatModel` adds 1 ms per beat to the wait, simulating scheduler overhead. Without it, beats landing exactly on the 4000 ms boundary give 7 beats where the real threaded Java run shows 6.
- `HeartModel` uses a fixed-seed LCG, written identically in Python and C++, instead of `Random(System.currentTimeMillis())`. Its output is therefore reproducible, but it does not match any Java run.
- `DJTestDrive` and `HeartTestDrive` are rewritten as scripted sessions (press Start, type 120, press `>>`, and so on) because the Java versions only open windows.
- Overloaded `registerObserver(BeatObserver)` / `registerObserver(BPMObserver)`: C++ keeps the overload; Python uses `register_beat_observer` / `register_bpm_observer`.
- Java lambdas used as observers in `BeatModelTestDrive` become `FunctionBeatObserver` / `FunctionBPMObserver` wrapper classes.

## Java vs Python vs C++ in this chapter

| Topic | Java | Python | C++ |
|-------|------|--------|-----|
| Interfaces (`Quackable`, `Observer`, `BeatModelInterface`) | `interface`; `Quackable extends QuackObservable` | `abc.ABC` + `@abstractmethod` | classes with pure virtuals plus `virtual ~X() = default` |
| Observer registration | `List<Observer>` holds strong references | list of strong references (cycles are collected by the GC) | `std::weak_ptr<Observer>`: ducks and models never own their observers, so view and model cannot form a `shared_ptr` cycle. Expired observers are skipped on notify |
| Overloaded `registerObserver` | overloads on interface type; `DJView` casts `(BeatObserver) this` | not possible, so two method names | overloads on `shared_ptr<BeatObserver>` / `shared_ptr<BPMObserver>`; `DJView` is both, so it registers with `static_pointer_cast` |
| Observable helper and `this` | `new Observable(this)` | `Observable(self)` | each duck owns an `Observable` by value, which keeps a non-owning `const QuackObservable*` back pointer; copying is deleted so the pointer stays valid |
| `DJView` registering itself | in the constructor | in `__init__` | needs `shared_ptr` to itself, so a private ctor plus `DJView::create()` using `enable_shared_from_this` |
| Decorator and Composite ownership | references | references | `shared_ptr<Quackable>` (a duck can sit in several flocks); the controller owns its view and the view borrows the controller by raw pointer |
| `static int numberOfQuacks` | `static` field | class attribute | `inline static` member (C++17, no out-of-class definition) |
| `toString()` | `Object.toString()` override | `__str__` | virtual `toString()` on `QuackObservable` with a default |
| Lambdas as listeners | `BeatObserver` is a functional interface, so a lambda converts directly | any callable, or a small wrapper class | `std::function` held in a `FunctionBeatObserver` wrapper (an interface with a `shared_ptr` identity needs a class) |
| Duplicated duck classes | four near-identical classes | one `_ObservableDuck` base parameterised by sound and name | one header per duck, generated from the same template |
| Time and threads | `Thread` + `sleep` | manual clock | manual clock |
| Files | one public class per file | grouped by concept | headers per concept, `.cpp` per entry point |

## Verification

- Java compiled in a scratch directory. `DuckSimulator` and `BeatModelTestDrive` were run. `DJTestDrive` and `HeartTestDrive` only compile (they need a display).
- `DuckSimulator`: Python and C++ output match Java exactly.
- `BeatModelTestDrive`: Python and C++ match Java exactly (the real run is thread-timed, and the 1 ms overhead above makes the simulation agree).
- `DJTestDrive`, `HeartTestDrive`: no Java output to compare (GUI). Python and C++ outputs are identical to each other.
- C++ builds with `-std=c++17 -Wall -Wextra -pedantic` and no warnings.
