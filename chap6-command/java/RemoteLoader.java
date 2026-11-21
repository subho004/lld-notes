/**
 * Client: creates receivers and concrete commands, loads them into the RemoteControl slots, and builds the party macros.
 */
public class RemoteLoader {
    public static void main(String[] args) {
        RemoteControl remoteControl = new RemoteControl();

        Light livingRoomLight = new Light("Living Room");
        Light kitchenLight = new Light("Kitchen");
        CeilingFan ceilingFan = new CeilingFan("Living Room");
        CelingFanv2 ceilingFanV2 = new CelingFanv2("Living Room");
        GarageDoor garageDoor = new GarageDoor("Garage");
        Stereo stereo = new Stereo("Living Room");

        LightOnCommand livingRoomLightOn = new LightOnCommand(livingRoomLight);
        LightOffCommand livingRoomLightOff = new LightOffCommand(livingRoomLight);
        LightOnCommand kitchenLightOn = new LightOnCommand(kitchenLight);
        LightOffCommand kitchenLightOff = new LightOffCommand(kitchenLight);

        CeilingFanOnCommand ceilingFanOn = new CeilingFanOnCommand(ceilingFan);
        CeilingFanOffCommand ceilingFanOff = new CeilingFanOffCommand(ceilingFan);

        CeilingFanHighCommand ceilingFanHigh = new CeilingFanHighCommand(ceilingFanV2);
        CeilingFanv2OffCommand ceilingFanV2Off = new CeilingFanv2OffCommand(ceilingFanV2);

        GarageDoorUpCommand garageDoorUp = new GarageDoorUpCommand(garageDoor);
        GarageDoorDownCommand garageDoorDown = new GarageDoorDownCommand(garageDoor);

        StereoOnWithCDCommand stereoOnWithCD = new StereoOnWithCDCommand(stereo);
        StereoOffCommand stereoOff = new StereoOffCommand(stereo);

        remoteControl.setCommand(0, livingRoomLightOn, livingRoomLightOff);
        remoteControl.setCommand(1, kitchenLightOn, kitchenLightOff);
        remoteControl.setCommand(2, ceilingFanOn, ceilingFanOff);
        remoteControl.setCommand(3, ceilingFanHigh, ceilingFanV2Off);
        remoteControl.setCommand(4, stereoOnWithCD, stereoOff);
        remoteControl.setCommand(5, garageDoorUp, garageDoorDown);

        // Macro commands bundle several commands behind a single slot.
        Command[] partyOn = { livingRoomLightOn, kitchenLightOn, ceilingFanOn,
                ceilingFanHigh, stereoOnWithCD };
        Command[] partyOff = { livingRoomLightOff, kitchenLightOff, ceilingFanOff,
                ceilingFanV2Off, stereoOff };
        MacroCommand partyOnMacro = new MacroCommand(partyOn);
        MacroCommand partyOffMacro = new MacroCommand(partyOff);

        remoteControl.setCommand(6, partyOnMacro, partyOffMacro);

        System.out.println(remoteControl);

        System.out.println("\n--- Individual slots ---");
        remoteControl.onButtonWasPushed(0);
        remoteControl.offButtonWasPushed(0);
        remoteControl.onButtonWasPushed(2);
        remoteControl.offButtonWasPushed(2);
        remoteControl.onButtonWasPushed(3);
        remoteControl.offButtonWasPushed(3);

        System.out.println("\n--- Party mode ON (slot 6) ---");
        remoteControl.onButtonWasPushed(6);

        System.out.println("\n--- Party mode OFF (slot 6) ---");
        remoteControl.offButtonWasPushed(6);

        System.out.println("\n--- Undo party off ---");
        remoteControl.undoButtonWasPushed();
    }
}
