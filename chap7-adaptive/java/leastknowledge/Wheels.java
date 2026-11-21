package leastknowledge;

/** Component owned by Car; clients never reach it directly. */
public class Wheels {
    public void rotate() {
        System.out.println("Wheels rotating");
    }

    public void stop() {
        System.out.println("Wheels stopped");
    }
}
