/** Concrete Strategy: normal flying; the default in Duck. */
public class FlyWithWings implements FlyBehavior {
    public void fly() {
        System.out.println("I'm flying!!");
    }
}