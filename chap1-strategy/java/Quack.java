/** Concrete Strategy: ordinary quack; the default in Duck and DuckCall. */
public class Quack implements QuackBehavior {
    public void quack() {
        System.out.println("Quack");
    }
}