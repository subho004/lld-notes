package leastknowledge;

/** Principle of Least Knowledge: Car coordinates its own Engine, Wheels and Doors so clients only call Car. */
public class Car {
    private Engine engine;
    private Wheels wheels;
    private Doors doors;

    public Car(Engine engine, Wheels wheels, Doors doors) {
        this.engine = engine;
        this.wheels = wheels;
        this.doors = doors;
    }

        // Car decides the order (unlock, then start); clients don't touch the parts.
    public void start() {
        doors.unlock();
        engine.start();
    }

        // Guard based on engine state, hidden from the client.
    public void drive() {
        if (!engine.isRunning()) {
            System.out.println("Cannot drive - start the car first");
            return;
        }
        wheels.rotate();
        System.out.println("Driving...");
    }

    public void stop() {
        wheels.stop();
        engine.stop();
    }

        // Composes stop() with locking the doors.
    public void park() {
        stop();
        doors.lock();
        System.out.println("Parked");
    }

        // Only allowed when the engine is off.
    public void refuel() {
        if (engine.isRunning()) {
            System.out.println("Cannot refuel while engine is running");
            return;
        }
        System.out.println("Refueling...");
    }
}
