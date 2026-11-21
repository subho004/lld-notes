/** Concrete Strategy: rocket flight; typically swapped in at runtime. */
public class FlyRocketPowered implements FlyBehavior {
    public void fly() {
        System.out.println("I'm flying with a rocket!");
    }
}