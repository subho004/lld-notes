# Chapter 1 – Strategy Pattern

**Intent:** define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from the clients that use it.

**Design principles from the chapter**
- Identify the aspects that vary and separate them from what stays the same.
- Program to an interface, not an implementation.
- Favor composition over inheritance.

## Structure

```
Duck (context)  ──has-a──▶ FlyBehavior   ◀── FlyWithWings / FlyNoWay / FlyRocketPowered
                └─has-a──▶ QuackBehavior ◀── Quack / Squeak / MuteQuack
MallardDuck, ModelDuck extend Duck;  DuckCall uses QuackBehavior on its own
```

`Duck` delegates `performFly()` / `performQuack()` to its behavior objects. Behaviors can be swapped at runtime (`setFlyBehavior`), which is what `ModelDuck` demonstrates when it gets a rocket.

## Layout and how to run

| Language | Folder    | Run |
|----------|-----------|-----|
| Java     | `java/`   | `javac -d out *.java && java -cp out MiniDuckSimulator` |
| Python   | `python/` | `python3 mini_duck_simulator.py` |
| C++      | `cpp/`    | `make run` (needs a C++17 compiler) |

All three print identical output.

## Java vs Python vs C++ in this chapter

| Topic | Java | Python | C++ |
|-------|------|--------|-----|
| Interface | `interface FlyBehavior` | `abc.ABC` + `@abstractmethod` | class with pure virtual method (`= 0`) |
| Ownership of strategy | GC-managed reference | GC-managed reference | `std::unique_ptr<FlyBehavior>`: the duck owns its strategy, and setters take ownership with `std::move` |
| Cleanup | automatic | automatic | base class needs a `virtual ~FlyBehavior() = default`; without it, deleting through the base pointer is undefined behavior |
| Override checking | `@Override` (optional) | none | `override` keyword (compile error if the signature doesn't match) |
| Default strategy in base ctor | `new FlyWithWings()` | `FlyWithWings()` | `std::make_unique<FlyWithWings>()` |
| Files | one public class per file | grouped by concept (behaviors together) | headers per concept, one `.cpp` with `main` |
