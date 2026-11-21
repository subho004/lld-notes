/** Concrete Strategy: rubber-duck squeak. */
public class Squeak implements QuackBehavior {
    public void quack() {
        System.out.println("Squeak");
    }
}