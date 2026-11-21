# Chapter 2 – Observer Pattern

**Intent:** define a one-to-many dependency between objects so that when one object (the subject) changes state, all of its dependents (observers) are notified and updated automatically.

**Design principles from the chapter**
- Strive for loosely coupled designs between objects that interact.
- (Carried over from chapter 1) Program to an interface, not an implementation.
- (Carried over) Favor composition over inheritance.

## Structure

```
Subject (interface)  ◀── WeatherData   (holds a list of Observers, setMeasurements() -> notifyObservers())
Observer (interface) ◀── CurrentConditionsDisplay, StatisticsDisplay, ForecastDisplay, HeatIndexDisplay
DisplayElement       ◀── the same four displays (display())

push (top level): observer.update(temperature, humidity, pressure)
pull (pull/):     observer.update()  ->  observer calls weatherData.getTemperature() etc.
```

`SwingObserverExample` shows the same pattern in a GUI toolkit: `JButton` is the subject, `ActionListener`s are the observers.

## Layout and how to run

| Language | Folder | Run |
|----------|--------|-----|
| Java push model | `java/` | `javac -d out *.java && java -cp out WeatherStation` |
| Java Swing example | `java/` | `java -cp out SwingObserverExample [lambda]` (needs a display; throws `HeadlessException` otherwise) |
| Java pull model | `java/pull/` | `javac -d out pull/*.java && java -cp out pull.WeatherStation` |
| Python push | `python/` | `python3 weather_station.py` and `python3 swing_observer_example.py [lambda]` |
| Python pull | `python/pull/` | `cd python/pull && python3 weather_station.py` |
| C++ push | `cpp/` | `make run` (builds `WeatherStation` and `SwingObserverExample`) |
| C++ pull | `cpp/pull/` | `cd cpp/pull && make run` |

Python modules: `observer.py` (Observer/DisplayElement/Subject), `weather_data.py`, `displays.py` (the four displays), `weather_station.py`, `swing_observer_example.py`, `java_float.py`. C++ headers: `Observer.h`, `WeatherData.h`, `Displays.h`, `JavaFloat.h`.

## Java vs Python vs C++ in this chapter

| Topic | Java | Python | C++ |
|-------|------|--------|-----|
| Interfaces | `interface Observer`, `Subject`, `DisplayElement` | `abc.ABC` classes; a display inherits two of them | abstract classes with pure virtuals, multiple inheritance, virtual destructors |
| Subject's reference to observers | `List<Observer>` (strong, GC) | `list` (strong, GC) | `std::vector<std::weak_ptr<Observer>>`: the subject observes without owning, so there is no observer -> subject -> observer ownership cycle and a destroyed observer is skipped safely |
| Registering from the constructor | `weatherData.registerObserver(this)` | `register_observer(self)` | a `shared_ptr` to `this` can't be made in a constructor, so displays are built with a `static create()` factory that uses `enable_shared_from_this`/`shared_ptr` and then registers |
| Lifetime of observers | alive while referenced (the subject's list keeps them alive; the pull `new X(wd)` calls rely on this) | same | the caller owns them (`auto d = X::create(wd)`); when the last `shared_ptr` dies the subject silently drops it |
| removeObserver | `List.remove(o)` (uses `equals`) | `list.remove` | `remove_if` comparing locked `shared_ptr`s (also prunes expired entries) |
| Mutation during notify | `ConcurrentModificationException` if an observer unregisters mid-loop | I iterate over a copy | iterate over a copy of the weak_ptr vector |
| Push vs pull | `update(t,h,p)` vs `update()` + getters | same | same; the pull displays keep a `WeatherData&` (the subject outlives its displays in `main`) |
| Listener objects vs lambdas | `ActionListener` (functional interface) + lambda | callable accepted directly, or an `ActionListener` object | `std::function<void(const ActionEvent&)>` for lambdas, `shared_ptr<ActionListener>` for classes |
| `float` | 32-bit; `Float.toString` gives shortest round-trip text | Python floats are 64-bit; `java_float.py` rounds to float32 (`struct`) after each step and formats like Java | native `float`; `JavaFloat.h` mimics `Float.toString` (iostream would print `80` / `80.755` differently) |
| Built-in observer support | `java.util.Observable` (deprecated, not used here) | none | none |

## Simulation deviations

- **Swing:** `JFrame`/`JButton` need a display, and the Java version throws `HeadlessException` when run headless. The Python and C++ versions use tiny `FakeFrame`/`FakeButton` classes. The frame "shows" itself by printing one line, and `main` plays the user by calling `button.click()` once, which fires the angel and devil listeners in registration order. The Java program would print only the two listener messages when a person clicks. The two extra lines (`[frame ...]`, `[user clicks the button]`) are simulation-only. Both `normal` and `lambda` modes are supported.
- Python/C++ print floats Java style (`80.0`, `80.755`) via the helper, so the weather output matches Java byte for byte.

## Verification

- `WeatherStation` (push) and `pull.WeatherStation`: Java, Python, and C++ stdout identical (diffed).
- `SwingObserverExample`: Java could not run headless; Python and C++ produce identical output to each other for both modes. The Java listeners' text matches.
- C++ compiled with `-std=c++17 -Wall -Wextra -pedantic`, zero warnings. Build output, `__pycache__`, and `.class` files were removed.
