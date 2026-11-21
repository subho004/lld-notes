// Simplest Invoker: holds one Command and triggers it on button press.
#pragma once
#include "Command.h"

// Invoker with a single slot.
class SimpleRemoteControl {
    CommandPtr slot;

public:
    void setCommand(CommandPtr command) { slot = std::move(command); }
    void buttonWasPressed() { slot->execute(); }
    void undoButtonWasPressed() { slot->undo(); }
};
