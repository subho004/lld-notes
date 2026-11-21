// Command interface (pattern role: Command) plus the generic commands:
// NoCommand (Null Object), LambdaCommand, MacroCommand. Header-only for simplicity.
#pragma once
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Abstract Command; virtual destructor so commands are safely deleted via shared_ptr<Command>.
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    // Stand-in for Java's getClass().getName(), used by RemoteControl::toString().
    virtual std::string name() const = 0;
};

// shared_ptr: one command may sit in a remote slot and in a macro at the same time.
using CommandPtr = std::shared_ptr<Command>;

// Null Object: fills empty slots so the invoker needs no null checks.
class NoCommand : public Command {
public:
    void execute() override {}
    void undo() override {}
    std::string name() const override { return "NoCommand"; }
};

// Command built from two callables; replaces one class per action.
class LambdaCommand : public Command {
    std::function<void()> executeAction;
    std::function<void()> undoAction;

public:
    LambdaCommand(std::function<void()> executeAction, std::function<void()> undoAction)
        : executeAction(std::move(executeAction)), undoAction(std::move(undoAction)) {}
    void execute() override { executeAction(); }
    void undo() override { undoAction(); }
    std::string name() const override { return "LambdaCommand"; }
};

// Composite-like command: runs children in order, undoes them in reverse.
class MacroCommand : public Command {
    std::vector<CommandPtr> commands;

public:
    explicit MacroCommand(std::vector<CommandPtr> commands) : commands(std::move(commands)) {}
    void execute() override {
        for (auto& command : commands) command->execute();
    }
    void undo() override {
        // Reverse iterators: undo in the opposite order of execution.
        for (auto it = commands.rbegin(); it != commands.rend(); ++it) (*it)->undo();
    }
    std::string name() const override { return "MacroCommand"; }
};
