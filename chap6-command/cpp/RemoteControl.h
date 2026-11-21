// Invoker: depends only on the Command interface, never on receivers.
#pragma once
#include <array>
#include <sstream>
#include <string>

#include "Command.h"

// Invoker with 7 on/off slots and a one-level undo.
class RemoteControl {
    static constexpr int SLOTS = 7;
    std::array<CommandPtr, SLOTS> onCommands;
    std::array<CommandPtr, SLOTS> offCommands;
    CommandPtr undoCommand;

public:
    RemoteControl() {
        // Null Object fills every slot (one shared instance), avoiding null checks.
        CommandPtr noCommand = std::make_shared<NoCommand>();
        undoCommand = noCommand;
        onCommands.fill(noCommand);
        offCommands.fill(noCommand);
    }

    void setCommand(int slot, CommandPtr onCommand, CommandPtr offCommand) {
        onCommands[slot] = std::move(onCommand);
        offCommands[slot] = std::move(offCommand);
    }

    void onButtonWasPushed(int slot) {
        // Remember the last command so undo can reverse it.
        undoCommand = onCommands[slot];
        onCommands[slot]->execute();
    }

    void offButtonWasPushed(int slot) {
        undoCommand = offCommands[slot];
        offCommands[slot]->execute();
    }

    void undoButtonWasPushed() { undoCommand->undo(); }

    std::string toString() const {
        std::ostringstream out;
        // name() replaces Java reflection; typeid().name() would be mangled.
        out << "\n------ Remote Control ------\n";
        for (int i = 0; i < SLOTS; i++) {
            out << "[slot " << i << "] " << onCommands[i]->name() << "    " << offCommands[i]->name() << "\n";
        }
        return out.str();
    }
};
