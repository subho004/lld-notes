/**
 * Adaptee: a class with an incompatible interface (honk instead of quack) that GooseAdapter wraps.
 */
public class Goose {
    public void honk() {
        System.out.println("Honk");
    }
}
