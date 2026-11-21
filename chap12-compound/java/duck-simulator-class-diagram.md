# Duck Simulator — Compound Patterns Class Diagram

A bird’s-eye view of the Chapter 12 duck simulator: **Abstract Factory**, **Decorator**, **Adapter**, **Composite**, and **Observer** packed into one design.

## Mermaid class diagram

```mermaid
classDiagram
    direction TB

    class DuckSimulator {
        +main(String[] args)
        +simulate(AbstractDuckFactory)
        +simulate(Quackable)
    }

    class AbstractDuckFactory {
        <<abstract>>
        +createMallardDuck() Quackable
        +createRedheadDuck() Quackable
        +createDuckCall() Quackable
        +createRubberDuck() Quackable
    }

    class DuckFactory {
        +createMallardDuck() Quackable
        +createRedheadDuck() Quackable
        +createDuckCall() Quackable
        +createRubberDuck() Quackable
    }

    class CountingDuckFactory {
        +createMallardDuck() Quackable
        +createRedheadDuck() Quackable
        +createDuckCall() Quackable
        +createRubberDuck() Quackable
    }

    class QuackObservable {
        <<interface>>
        +registerObserver(Observer)
        +notifyObservers()
    }

    class Quackable {
        <<interface>>
        +quack()
    }

    class Observer {
        <<interface>>
        +update(QuackObservable)
    }

    class Quackologist {
        +update(QuackObservable)
    }

    class Observable {
        -List~Observer~ observers
        -QuackObservable duck
        +registerObserver(Observer)
        +notifyObservers()
    }

    class MallardDuck {
        -Observable observable
        +quack()
        +registerObserver(Observer)
        +notifyObservers()
    }

    class RedheadDuck {
        -Observable observable
        +quack()
        +registerObserver(Observer)
        +notifyObservers()
    }

    class DuckCall {
        -Observable observable
        +quack()
        +registerObserver(Observer)
        +notifyObservers()
    }

    class RubberDuck {
        -Observable observable
        +quack()
        +registerObserver(Observer)
        +notifyObservers()
    }

    class GooseAdapter {
        -Goose goose
        -Observable observable
        +quack()
        +registerObserver(Observer)
        +notifyObservers()
    }

    class Goose {
        +honk()
    }

    class Flock {
        -List~Quackable~ ducks
        +add(Quackable)
        +quack()
        +registerObserver(Observer)
        +notifyObservers()
    }

    class QuackCounter {
        -Quackable duck
        +getQuacks()$ int
        +quack()
        +registerObserver(Observer)
        +notifyObservers()
    }

    DuckSimulator --> AbstractDuckFactory : uses
    DuckSimulator --> Quackable : simulates
    DuckSimulator --> Quackologist : creates
    DuckSimulator --> Flock : builds

    AbstractDuckFactory <|-- DuckFactory
    AbstractDuckFactory <|-- CountingDuckFactory
    AbstractDuckFactory ..> Quackable : creates

    QuackObservable <|-- Quackable
    Quackable <|.. MallardDuck
    Quackable <|.. RedheadDuck
    Quackable <|.. DuckCall
    Quackable <|.. RubberDuck
    Quackable <|.. GooseAdapter
    Quackable <|.. Flock
    Quackable <|.. QuackCounter

    Observer <|.. Quackologist
    QuackObservable <|.. Observable

    MallardDuck *-- Observable : delegates
    RedheadDuck *-- Observable : delegates
    DuckCall *-- Observable : delegates
    RubberDuck *-- Observable : delegates
    GooseAdapter *-- Observable : delegates
    GooseAdapter --> Goose : adapts

    QuackCounter o-- Quackable : decorates
    Flock o-- Quackable : composites

    Quackologist ..> QuackObservable : observes
    Observable --> Observer : notifies
```

## Patterns in this design

| Pattern              | Role in the simulator                                                                               |
| -------------------- | --------------------------------------------------------------------------------------------------- |
| **Abstract Factory** | `AbstractDuckFactory` / `DuckFactory` / `CountingDuckFactory` create families of `Quackable`s       |
| **Decorator**        | `QuackCounter` wraps ducks to count quacks                                                          |
| **Adapter**          | `GooseAdapter` makes a `Goose` look like a `Quackable`                                              |
| **Composite**        | `Flock` treats a collection of `Quackable`s as one `Quackable`                                      |
| **Observer**         | `QuackObservable` / `Observable` / `Observer` / `Quackologist` track individual quacks in real time |

## Product families

- **DuckFactory** — plain ducks (no counting)
- **CountingDuckFactory** — ducks wrapped in `QuackCounter` decorators

The simulator only depends on `AbstractDuckFactory` and `Quackable`; it never cares which concrete duck or decorator it got.

## Quackable variants

All implement `Quackable` (and therefore `QuackObservable`):

- **Ducks:** `MallardDuck`, `RedheadDuck`, `DuckCall`, `RubberDuck`
- **Adapter:** `GooseAdapter` (wraps `Goose`)
- **Composite:** `Flock` (holds other `Quackable`s, including nested flocks)
- **Decorator:** `QuackCounter` (adds counting behavior)

Each duck composes an `Observable` helper and delegates `registerObserver` / `notifyObservers` to it. `QuackCounter` and `Flock` forward registration to their children/wrapped duck so observers hear every leaf quack.
