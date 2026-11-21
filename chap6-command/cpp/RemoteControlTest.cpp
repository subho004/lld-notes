// Client demo: SimpleRemoteControl (one slot) driving a light and a garage door.
#include <memory>

#include "Commands.h"
#include "Devices.h"
#include "SimpleRemoteControl.h"

int main() {
    SimpleRemoteControl remote;
    auto light = std::make_shared<Light>();
    auto lightOn = std::make_shared<LightOnCommand>(light);
    remote.setCommand(lightOn);
    remote.buttonWasPressed();
    remote.undoButtonWasPressed();

    auto garageDoor = std::make_shared<GarageDoor>();
    auto garageDoorOpen = std::make_shared<GarageDoorOpenCommand>(garageDoor);
    remote.setCommand(garageDoorOpen);
    remote.buttonWasPressed();
    remote.undoButtonWasPressed();
    return 0;
}
