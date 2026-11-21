# Chapter 6 – Command Pattern

**Intent:** encapsulate a request as an object, thereby letting you parameterize other objects with different requests, queue or log requests, and support undoable operations.

**Design principles from the chapter**
- Encapsulate what varies (here, the request: "who does what").
- Decouple the invoker from the receiver: the remote knows only the `Command` interface, never `Light` or `Stereo`.
- Program to an interface, not an implementation.
- Related ideas: the Null Object (`NoCommand`), macro commands (Composite-like), undo by storing prior state.

## Structure

```
Client (RemoteLoader) creates ──▶ ConcreteCommand(receiver) ──▶ Receiver (Light, Stereo, GarageDoor, ...)
Invoker (RemoteControl / SimpleRemoteControl) holds Command slots and calls execute() / undo()

            «interface» Command { execute(); undo() }
                 ▲
  LightOnCommand, LightOffCommand, CeilingFan*Command, GarageDoor*Command,
  StereoOnWithCDCommand, StereoOffCommand, NoCommand,
  MacroCommand (holds Command[]), LambdaCommand (holds two Runnables)
```

## Layout and how to run

| Language | Folder    | Run |
|----------|-----------|-----|
| Java     | `java/`   | `javac -d out *.java && java -cp out RemoteLoader` (also `RemoteControlTest`, `RemoteControlLambda`) |
| Python   | `python/` | `python3 remote_loader.py` (also `remote_control_test.py`, `remote_control_lambda.py`) |
| C++      | `cpp/`    | `make run` (builds `RemoteControlTest`, `RemoteControlLambda`, `RemoteLoader`; C++17) |

Python modules: `devices.py` (receivers), `command.py` (interface + NoCommand/LambdaCommand/MacroCommand), `commands.py` (concrete commands), `remote_control.py`, `simple_remote_control.py`. C++ headers mirror these: `Devices.h`, `Command.h`, `Commands.h`, `RemoteControl.h`, `SimpleRemoteControl.h`.

## Java vs Python vs C++ in this chapter

| Topic | Java | Python | C++ |
|-------|------|--------|-----|
| Command interface | `interface Command` | `abc.ABC` with abstract `execute`/`undo` | abstract class, pure virtual methods, virtual destructor |
| Lambda commands | `Runnable` fields; multi-statement lambdas allowed | `Callable[[], None]`; lambdas are single-expression, so the stereo "on with CD" action is a nested `def` | `std::function<void()>`; lambdas capture `shared_ptr` receivers by value |
| Lifetime of receivers | GC | GC | `std::shared_ptr` for receivers and commands, since the same command sits in a slot and in a macro, and receivers are shared by several commands |
| Arrays of commands | `Command[]` | `list` | `std::array<CommandPtr, 7>` for slots, `std::vector<CommandPtr>` for macros |
| Null object | `NoCommand` fills every slot | same | same, one shared `NoCommand` instance |
| Class name in `toString()` | `getClass().getName()` | `type(x).__name__` | no portable reflection (`typeid().name()` is mangled), so each command overrides a `name()` method |
| Duplicate undo logic | repeated in each fan-speed class | `_CeilingFanSpeedCommand` base class | `CeilingFanSpeedCommand` base class |
| Constants | `static final int` | class attributes | `static constexpr int` |
| Undo of macro | reverse `for` loop | `reversed()` | reverse iterators |

## Deviations

- Java `GarageDoorUpCommand` and `GarageDoorOpenCommand` are identical; kept as separate classes in C++, and in Python `GarageDoorUpCommand` subclasses `GarageDoorOpenCommand` (so its printed name is still `GarageDoorUpCommand`).
- `CelingFanv2` keeps the repo's spelling. `RemoteControlLambda` prints a trailing extra blank line after the slot table because `println(remoteControl)` follows a string ending in a newline; C++ and Python reproduce this.
- No GUI, network or randomness is involved in this chapter.

## Verification

Java compiled into a scratch directory; stdout of `RemoteControlTest`, `RemoteControlLambda` and `RemoteLoader` diffed against Python and C++ output: all identical. C++ builds with `-std=c++17 -Wall -Wextra -pedantic` with zero warnings.
