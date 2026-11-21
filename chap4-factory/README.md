# Chapter 4 – Factory Patterns (Factory Method and Abstract Factory)

**Factory Method intent:** define an interface for creating an object, but let subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.

**Abstract Factory intent:** provide an interface for creating families of related or dependent objects without specifying their concrete classes.

**Design principles from the chapter**
- Depend upon abstractions. Do not depend upon concrete classes (Dependency Inversion Principle).
- Program to an interface, not an implementation (carried over from chapter 1).
- Encapsulate what varies: object creation is pulled out of `orderPizza()`.

## Structure

```
Simple Factory (a warm-up, not a GoF pattern)
  SamplePizzaFactory.createPizza(type) ──▶ CheesePizza / PepperoniPizza / ClamPizza / VeggiePizza

Factory Method                                   (creator hierarchy parallels product hierarchy)
  PizzaStore.orderPizza()  ──calls──▶  createPizza()   <<abstract>>
    ├─ NYStylePizzaStore         ──▶ NYStyle{Cheese,Pepperoni,Clam,Veggie}Pizza
    └─ CaliforniaStylePizzaStore ──▶ California{...}Pizza
  DependentPizzaStore: the "before" picture, one class that knows every concrete pizza

Abstract Factory
  PizzaStore2.orderPizza() ──▶ createPizza() builds a Pizza2 with a regional IngredientFactory
    NYPizzaStore2 / ChicagoPizzaStore2
  IngredientFactory { createDough, createSauce, createCheese, createVeggies, createPepperoni, createClam }
    ├─ NYPizzaIngredientFactory      (ThinCrustDough, MarinaraSauce, ReggianoCheese, FreshClams ...)
    └─ ChicagoPizzaIngredientFactory (ThickCrustDough, PlumTomatoSauce, MozzarellaCheese, FrozenClams ...)
  Pizza2 { CheesePizza2, VeggiePizza2, PepperoniPizza2, ClamPizza2 } hold only the factory and ask it for ingredients
```

## Layout and how to run

All Java sources are flat (no sub-folders), so Python and C++ are flat too.

| Language | Folder    | Entry points | Run |
|----------|-----------|--------------|-----|
| Java     | `java/`   | `PizzaShop`, `PizzaShop2`, `DependentPizzaStore` | `javac -d out *.java && java -cp out PizzaShop2` |
| Python   | `python/` | `pizza_shop.py`, `pizza_shop2.py`, `dependent_pizza_store.py` | `python3 pizza_shop2.py` (or `PYTHONPATH=. python3 ...`) |
| C++      | `cpp/`    | `PizzaShop.cpp`, `PizzaShop2.cpp`, `DependentPizzaStore.cpp` | `make run` (needs a C++17 compiler); binaries land in `build/` |

How the 56 Java files are grouped:

| Concept | Python module | C++ header |
|---------|---------------|-----------|
| Ingredient interfaces + all 16 concrete ingredients | `ingredients.py` | `Ingredients.h` |
| `IngredientFactory`, NY and Chicago factories | `ingredient_factory.py` | `IngredientFactory.h` |
| `Pizza` and all string-based pizzas (simple, NY, Chicago, California) | `pizza.py` | `Pizza.h` |
| `SamplePizzaFactory` | `sample_pizza_factory.py` | `SamplePizzaFactory.h` |
| `PizzaStore`, `NYStylePizzaStore`, `CaliforniaStylePizzaStore` | `pizza_store.py` | `PizzaStore.h` |
| `DependentPizzaStore` | `dependent_pizza_store.py` (has `main`) | `DependentPizzaStore.h` + `.cpp` |
| `Pizza2` and its four ingredient-driven pizzas | `pizza2.py` | `Pizza2.h` |
| `PizzaStore2`, `NYPizzaStore2`, `ChicagoPizzaStore2` | `pizza_store2.py` | `PizzaStore2.h` |

`SamplePizzaFactory` has no entry point that uses it in the Java code, so it is ported but unused (it compiles on its own).

## Java vs Python vs C++ in this chapter

| Topic | Java | Python | C++ |
|-------|------|--------|-----|
| Factory Method | `abstract Pizza createPizza(String)` (package-private) | `@abstractmethod create_pizza` | pure virtual `createPizza`, declared `protected` so only the store calls it |
| Returning "no pizza" | returns `null` for an unknown type (callers would NPE) | returns `None` (callers would get `AttributeError`) | returns an empty `unique_ptr`; dereferencing it is undefined behavior, so the same caveat applies |
| Product ownership | GC | GC | `orderPizza` returns `std::unique_ptr<Pizza>`: the caller owns the pizza, and reassigning `pizza = store->orderPizza(...)` destroys the previous one |
| Empty marker interfaces (`Dough`, `Sauce`, ...) | empty interfaces; printing uses `Object.toString()` | empty `ABC`; printing uses `__str__` | an empty class cannot be printed polymorphically, so each interface declares `virtual std::string toString() const = 0` |
| Ingredient families | `Veggies[]` array | `list` | `std::vector<std::unique_ptr<Veggies>>`: the pizza owns its ingredients, the factory hands over ownership |
| Sharing the Abstract Factory | plain reference held by pizza and store | plain reference | `std::shared_ptr<IngredientFactory>` handed to each pizza, since the store creates it and the pizza keeps using it |
| Polymorphic delete | automatic | automatic | every base class (`Pizza`, `PizzaStore`, `IngredientFactory`, ingredients) has a virtual destructor |
| `toString()` | `Object.toString()` override | `__str__` | member `toString()` plus `operator<<` for `Pizza2` |
| Duplicated store code | `NYPizzaStore2` and `ChicagoPizzaStore2` repeat an if/else chain | same logic factored into a module-level helper | factored into a protected static helper `createWith` in `PizzaStore2` (the names and flow are unchanged: `"New York Style Cheese Pizza"` etc.) |
| Subclass field setup | assign inherited fields in the constructor | `_init` helper fills inherited attributes | assign protected members in constructor bodies |
| Files | one public class per file (56) | 10 modules grouped by concept | 8 headers by concept plus 3 `.cpp` files with `main` |

## Verification

Java was compiled into a scratch directory and each entry point's stdout captured. The Python and C++ versions of `PizzaShop`, `PizzaShop2` and `DependentPizzaStore` produce output identical to Java (checked with `diff`). The C++ code builds with `-std=c++17 -Wall -Wextra -pedantic` and no warnings. There is no GUI, randomness or timing here, so no simulation was needed.
