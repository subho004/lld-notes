# Chapter 7 – Adapter and Facade Patterns

**Adapter intent:** convert the interface of a class into another interface clients expect. Adapter lets classes work together that couldn't otherwise because of incompatible interfaces.

**Facade intent:** provide a unified, simpler interface to a set of interfaces in a subsystem. Facade defines a higher-level interface that makes the subsystem easier to use.

**Design principle from the chapter**
- Principle of Least Knowledge (Law of Demeter): talk only to your immediate friends. Inside a method, only call methods on the object itself, objects passed in as parameters, objects the method creates, and the object's components. `leastknowledge/` shows a `Car` that coordinates its own `Engine`, `Wheels` and `Doors` so clients never reach into them.

## Structure

```
Client ──▶ Duck  ◀── TurkeyAdapter ──has-a──▶ Turkey (WildTurkey)
Client ──▶ Turkey ◀── DuckAdapter  ──has-a──▶ Duck   (MallardDuck)
Iterator    ◀── EnumerationIterator ──has-a──▶ Enumeration
Enumeration ◀── IteratorEnumeration ──has-a──▶ Iterator

Client ──▶ HomeTheaterFacade ──▶ Amplifier, Tuner, StreamingPlayer,
                                 Projector, TheaterLights, Screen, PopcornPopper
Client ──▶ Car ──▶ Engine, Wheels, Doors      (least knowledge)
```

The adapters hold the adaptee and translate calls (`quack` -> `gobble`; `fly` is repeated 5 times because a turkey only flies a short distance).

## Layout and how to run

| Language | Folder | Run |
|----------|--------|-----|
| Java | `java/` | `javac -d out java/*.java java/facade/*.java java/leastknowledge/*.java && java -cp out adaptive.DuckTestDrive` (also `adaptive.TurkeyTestDrive`, `adaptive.EnumerationIteratorTestDrive`, `adaptive.IteratorEnumerationTestDrive`, `facade.HomeTheaterTestDrive`, `leastknowledge.CarTestDrive`) |
| Python | `python/` | `python3 duck_test_drive.py`, `turkey_test_drive.py`, `enumeration_iterator_test_drive.py`, `iterator_enumeration_test_drive.py` |
| Python | `python/facade/` | `python3 home_theater_test_drive.py` |
| Python | `python/leastknowledge/` | `python3 car_test_drive.py` |
| C++ | `cpp/` | `make run` (builds the four adapter entry points) |
| C++ | `cpp/facade/` | `make run` |
| C++ | `cpp/leastknowledge/` | `make run` |

Python: `cd python && PYTHONPATH=. python3 <entry>.py` or plain `python3 <entry>.py` both work (stdlib only).

## Java vs Python vs C++ in this chapter

| Topic | Java | Python | C++ |
|-------|------|--------|-----|
| Target interface | `interface Duck` | `abc.ABC` + `@abstractmethod` | abstract class with pure virtuals and `virtual ~Duck() = default` |
| Holding the adaptee | plain reference | plain reference | `std::shared_ptr<Turkey>`: the adapter and `main` can both use the adaptee, and it is freed when the last owner goes away |
| Adapting generic types | `EnumerationIterator<T> implements Iterator<T>` | `Generic[T]` with `TypeVar` (hints only, not enforced) | `template <typename T> class EnumerationIterator : public Iterator<T>`, resolved at compile time; the adaptee is a `unique_ptr<Enumeration<T>>` the adapter owns |
| Library types | `java.util.Enumeration/Iterator/Vector` | tiny equivalents in `java_util.py` (Python's iterator protocol is different) | tiny equivalents in `JavaUtil.h` |
| Unsupported `remove()` | `UnsupportedOperationException` | `NotImplementedError` | `std::logic_error` |
| Facade subsystem | fields hold references | attributes | references to components owned by `main`, so the facade has no ownership and no copies; `[[maybe_unused]]` marks the unused `tuner`, as in Java |
| Least knowledge | `private` fields | `_name` convention, not enforced | `private:` members, and `Car` owns its parts through `unique_ptr`, so the parts cannot be reached from outside |
| Files | one public class per file | grouped by concept | headers per concept, `.cpp` per `main` |

## Notes

- No GUI, network or randomness is involved, so no simulation was needed.
- Java files declare `package adaptive/facade/leastknowledge` while `adaptive` sits directly in `java/`; compile with `javac -d out` as shown above (no source change needed).
- The Java `EnumerationIteratorTestDrive` uses a raw `new EnumerationIterator(...)` (compiles with an unchecked note); the ports are type-safe.

## Verification

All six entry points were run in Java, Python (both with and without `PYTHONPATH=.`) and C++ (`-std=c++17 -Wall -Wextra -pedantic`, zero warnings); stdout is byte-identical to Java in every case.
