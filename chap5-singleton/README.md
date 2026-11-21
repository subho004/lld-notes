# Chapter 5 – Singleton Pattern

**Intent:** ensure a class has only one instance and provide a global point of access to it.

**Design principles from the chapter**
- The Singleton is a pattern, not a principle: it trades some of "program to an interface" and loose coupling for a controlled global.
- Be careful with multithreading: a lazy `getInstance()` must be synchronized (or use eager init / double-checked locking / an enum).
- Keep the constructor private so nobody else can create instances.

## Structure

```
Singleton            - private static uniqueInstance; private ctor; static getInstance()
ChocolateBoiler      - Singleton (double-checked locking) + synchronized fill/boil/drain
SingletonEnum        - enum with one INSTANCE (Java's preferred idiom)
ChocoholicEnum       - second enum singleton, used by Chocoholic
```

## Layout and how to run

| Language | Folder    | Run |
|----------|-----------|-----|
| Java     | `java/`   | `javac -d out *.java && java -cp out SingletonTest` (also `ChocolateBoilerTest`, `SingletonEnumTest`, `Chocoholic`) |
| Python   | `python/` | `python3 singleton_test.py` (also `chocolate_boiler_test.py`, `singleton_enum_test.py`, `chocoholic.py`, `singleton_thread_demo.py`) |
| C++      | `cpp/`    | `make run` (C++17, uses `-pthread`); binaries in `build/` |

No sub-folders in this chapter. The four Java entry points print identical output in all three languages. `singleton_thread_demo.py` / `SingletonThreadDemo.cpp` are extras with no Java counterpart: 8 threads released together race on `getInstance()`, then hammer the boiler. Output is deterministic (one instance, 800 cycles, boiler empty).

## Java vs Python vs C++ in this chapter

| Topic | Java | Python | C++ |
|-------|------|--------|-----|
| Lazy thread-safe `getInstance` | `static synchronized` method | `threading.Lock` in a classmethod; or `__new__` with a lock | Meyers singleton: function-local `static` is initialised once, thread-safely, by the language (C++11) |
| Double-checked locking | `volatile` + `synchronized` block | check / `with lock` / check (the GIL makes the pointer read safe) | unnecessary; `std::call_once` + `std::once_flag` does it correctly (hand-written DCL needs `std::atomic`) |
| Enum singleton | `enum { INSTANCE; }`, serialization/reflection-safe | `Enum` with one member | no enum with methods; a Meyers singleton with deleted copy is the equivalent |
| Preventing extra instances | private constructor | convention only (`__new__` can enforce it) | private ctor + `= delete` copy/assign |
| Return type | reference to the object | reference | `T&`, never a raw owning pointer; storage is static, released at exit (`unique_ptr` in the call_once variants) |
| Synchronized methods | `synchronized` | `RLock` held per method | `std::recursive_mutex` + `lock_guard` (RAII); exposed so callers can make multi-step sequences atomic |
| Identity check | `==` | `is` | compare addresses (`&a == &b`) |
| Boolean output | `true` | `str(x).lower()` to match | `std::boolalpha` |

## Notes and verification

- Java has no threads in the repo code; the thread demo is added in Python/C++ only. `NewSingleton` (Python `__new__`) corresponds to `CallOnceSingleton` (C++ `std::call_once`) in the demo.
- Verified: Java was compiled in a scratch dir and the four entry points' stdout diffed against Python and C++, all identical. C++ compiles with `-std=c++17 -Wall -Wextra -pedantic` with zero warnings. Build output and `__pycache__` removed.
