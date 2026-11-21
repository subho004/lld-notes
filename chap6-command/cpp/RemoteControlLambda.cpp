// Client demo: slots filled with LambdaCommand instead of concrete command classes.
#include <iostream>
#include <memory>

#include "Command.h"
#include "Devices.h"
#include "RemoteControl.h"

int main() {
    RemoteControl remoteControl;

    auto livingRoomLight = std::make_shared<Light>("Living Room");
    auto kitchenLight = std::make_shared<Light>("Kitchen");
    auto ceilingFan = std::make_shared<CeilingFan>("Living Room");
    auto garageDoor = std::make_shared<GarageDoor>("Garage");
    auto stereo = std::make_shared<Stereo>("Living Room");

    // Lambdas capture the shared receivers by value (shared ownership keeps them alive).
    remoteControl.setCommand(0,
        std::make_shared<LambdaCommand>([=] { livingRoomLight->on(); }, [=] { livingRoomLight->off(); }),
        std::make_shared<LambdaCommand>([=] { livingRoomLight->off(); }, [=] { livingRoomLight->on(); }));

    remoteControl.setCommand(1,
        std::make_shared<LambdaCommand>([=] { kitchenLight->on(); }, [=] { kitchenLight->off(); }),
        std::make_shared<LambdaCommand>([=] { kitchenLight->off(); }, [=] { kitchenLight->on(); }));

    remoteControl.setCommand(2,
        std::make_shared<LambdaCommand>([=] { ceilingFan->on(); }, [=] { ceilingFan->off(); }),
        std::make_shared<LambdaCommand>([=] { ceilingFan->off(); }, [=] { ceilingFan->on(); }));

    remoteControl.setCommand(3,
        std::make_shared<LambdaCommand>(
            [=] {
                stereo->on();
                stereo->setCD();
                stereo->setVolume(11);
            },
            [=] { stereo->off(); }),
        std::make_shared<LambdaCommand>([=] { stereo->off(); }, [=] { stereo->on(); }));

    remoteControl.setCommand(4,
        std::make_shared<LambdaCommand>([=] { garageDoor->up(); }, [=] { garageDoor->down(); }),
        std::make_shared<LambdaCommand>([=] { garageDoor->down(); }, [=] { garageDoor->up(); }));

    std::cout << "------ Remote Control (Lambda) ------\n";
    std::cout << remoteControl.toString() << "\n";

    std::cout << "\n--- Slot 0: Living Room Light ---\n";
    remoteControl.onButtonWasPushed(0);
    remoteControl.undoButtonWasPushed();

    std::cout << "\n--- Slot 3: Stereo with CD ---\n";
    remoteControl.onButtonWasPushed(3);
    remoteControl.undoButtonWasPushed();

    std::cout << "\n--- Slot 4: Garage Door ---\n";
    remoteControl.onButtonWasPushed(4);
    remoteControl.undoButtonWasPushed();
    return 0;
}
