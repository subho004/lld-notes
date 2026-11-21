package leastknowledge;

/** Client: talks only to Car (Principle of Least Knowledge); the "bad" section only prints what not to do. */
public class CarTestDrive {
    public static void main(String[] args) {
        Car car = new Car(new Engine(), new Wheels(), new Doors());

        System.out.println("--- Good: client only talks to Car (Law of Demeter) ---");
        car.start();
        car.drive();
        car.park();
        car.refuel();

        System.out.println("\n--- Bad: reaching into Car's parts from outside ---");
        System.out.println("(This would violate the Law of Demeter)");
        System.out.println("car.getEngine().start();  // don't do this");
        System.out.println("car.getDoors().unlock();  // don't do this");
        System.out.println("Instead, call car.start() and let Car coordinate its components.");
    }
}
