// Client demo: creates receivers and commands, loads RemoteControl slots, runs a macro.
#include <iostream>
#include <memory>
#include <vector>

#include "Command.h"
#include "Commands.h"
#include "Devices.h"
#include "RemoteControl.h"

int main() {
    RemoteControl remoteControl;

    auto livingRoomLight = std::make_shared<Light>("Living Room");
    auto kitchenLight = std::make_shared<Light>("Kitchen");
    auto ceilingFan = std::make_shared<CeilingFan>("Living Room");
    auto ceilingFanV2 = std::make_shared<CelingFanv2>("Living Room");
    auto garageDoor = std::make_shared<GarageDoor>("Garage");
    auto stereo = std::make_shared<Stereo>("Living Room");

    auto livingRoomLightOn = std::make_shared<LightOnCommand>(livingRoomLight);
    auto livingRoomLightOff = std::make_shared<LightOffCommand>(livingRoomLight);
    auto kitchenLightOn = std::make_shared<LightOnCommand>(kitchenLight);
    auto kitchenLightOff = std::make_shared<LightOffCommand>(kitchenLight);

    auto ceilingFanOn = std::make_shared<CeilingFanOnCommand>(ceilingFan);
    auto ceilingFanOff = std::make_shared<CeilingFanOffCommand>(ceilingFan);

    auto ceilingFanHigh = std::make_shared<CeilingFanHighCommand>(ceilingFanV2);
    auto ceilingFanV2Off = std::make_shared<CeilingFanv2OffCommand>(ceilingFanV2);

    auto garageDoorUp = std::make_shared<GarageDoorUpCommand>(garageDoor);
    auto garageDoorDown = std::make_shared<GarageDoorDownCommand>(garageDoor);

    auto stereoOnWithCD = std::make_shared<StereoOnWithCDCommand>(stereo);
    auto stereoOff = std::make_shared<StereoOffCommand>(stereo);

    remoteControl.setCommand(0, livingRoomLightOn, livingRoomLightOff);
    remoteControl.setCommand(1, kitchenLightOn, kitchenLightOff);
    remoteControl.setCommand(2, ceilingFanOn, ceilingFanOff);
    remoteControl.setCommand(3, ceilingFanHigh, ceilingFanV2Off);
    remoteControl.setCommand(4, stereoOnWithCD, stereoOff);
    remoteControl.setCommand(5, garageDoorUp, garageDoorDown);

    // The same shared command objects sit in slots and inside the macros.
    std::vector<CommandPtr> partyOn = {livingRoomLightOn, kitchenLightOn, ceilingFanOn,
                                       ceilingFanHigh, stereoOnWithCD};
    std::vector<CommandPtr> partyOff = {livingRoomLightOff, kitchenLightOff, ceilingFanOff,
                                        ceilingFanV2Off, stereoOff};
    auto partyOnMacro = std::make_shared<MacroCommand>(partyOn);
    auto partyOffMacro = std::make_shared<MacroCommand>(partyOff);

    remoteControl.setCommand(6, partyOnMacro, partyOffMacro);

    std::cout << remoteControl.toString() << "\n";

    std::cout << "\n--- Individual slots ---\n";
    remoteControl.onButtonWasPushed(0);
    remoteControl.offButtonWasPushed(0);
    remoteControl.onButtonWasPushed(2);
    remoteControl.offButtonWasPushed(2);
    remoteControl.onButtonWasPushed(3);
    remoteControl.offButtonWasPushed(3);

    std::cout << "\n--- Party mode ON (slot 6) ---\n";
    remoteControl.onButtonWasPushed(6);

    std::cout << "\n--- Party mode OFF (slot 6) ---\n";
    remoteControl.offButtonWasPushed(6);

    std::cout << "\n--- Undo party off ---\n";
    remoteControl.undoButtonWasPushed();
    return 0;
}
