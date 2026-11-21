/**
 * Client demo: wires commands to a SimpleRemoteControl invoker and swaps the command in its single slot.
 */
public class RemoteControlTest {
    public static void main(String[] args) {
        SimpleRemoteControl remote = new SimpleRemoteControl();
        Light light = new Light();
        LightOnCommand lightOn = new LightOnCommand(light);
        remote.setCommand(lightOn);
        remote.buttonWasPressed();
        remote.undoButtonWasPressed();

        GarageDoor garageDoor = new GarageDoor();
        GarageDoorOpenCommand garageDoorOpen = new GarageDoorOpenCommand(garageDoor);
        remote.setCommand(garageDoorOpen);
        remote.buttonWasPressed();
        remote.undoButtonWasPressed();
    }
}
