/**
 * Client demo: builds commands from lambdas via LambdaCommand instead of concrete command classes.
 * Prints a trailing extra blank line after the slot table (println of a string ending in newline).
 */
public class RemoteControlLambda {
        public static void main(String[] args) {
                RemoteControl remoteControl = new RemoteControl();

                Light livingRoomLight = new Light("Living Room");
                Light kitchenLight = new Light("Kitchen");
                CeilingFan ceilingFan = new CeilingFan("Living Room");
                GarageDoor garageDoor = new GarageDoor("Garage");
                Stereo stereo = new Stereo("Living Room");

                remoteControl.setCommand(0,
                                new LambdaCommand(() -> livingRoomLight.on(), () -> livingRoomLight.off()),
                                new LambdaCommand(() -> livingRoomLight.off(), () -> livingRoomLight.on()));

                remoteControl.setCommand(1,
                                new LambdaCommand(() -> kitchenLight.on(), () -> kitchenLight.off()),
                                new LambdaCommand(() -> kitchenLight.off(), () -> kitchenLight.on()));

                remoteControl.setCommand(2,
                                new LambdaCommand(() -> ceilingFan.on(), () -> ceilingFan.off()),
                                new LambdaCommand(() -> ceilingFan.off(), () -> ceilingFan.on()));

                remoteControl.setCommand(3,
                                new LambdaCommand(() -> {
                                        stereo.on();
                                        stereo.setCD();
                                        stereo.setVolume(11);
                                }, () -> stereo.off()),
                                new LambdaCommand(() -> stereo.off(), () -> stereo.on()));

                remoteControl.setCommand(4,
                                new LambdaCommand(() -> garageDoor.up(), () -> garageDoor.down()),
                                new LambdaCommand(() -> garageDoor.down(), () -> garageDoor.up()));

                System.out.println("------ Remote Control (Lambda) ------");
                System.out.println(remoteControl);

                System.out.println("\n--- Slot 0: Living Room Light ---");
                remoteControl.onButtonWasPushed(0);
                remoteControl.undoButtonWasPushed();

                System.out.println("\n--- Slot 3: Stereo with CD ---");
                remoteControl.onButtonWasPushed(3);
                remoteControl.undoButtonWasPushed();

                System.out.println("\n--- Slot 4: Garage Door ---");
                remoteControl.onButtonWasPushed(4);
                remoteControl.undoButtonWasPushed();
        }
}
