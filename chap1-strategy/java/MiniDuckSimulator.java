/** Client/demo: shows default behaviors, runtime strategy swap, and a standalone DuckCall. */
public class MiniDuckSimulator {
    public static void main(String[] args) {
        System.out.println("Mallard Duck");
        Duck mallard = new MallardDuck();
        mallard.performFly();
        mallard.performQuack();

        System.out.println("Model Duck");
        Duck model = new ModelDuck();
        model.performFly();
        // Runtime swap: the same duck now flies differently.
        model.setFlyBehavior(new FlyRocketPowered());
        model.performFly();

        System.out.println("Duck Call!");
        DuckCall duckCall = new DuckCall();
        duckCall.performQuack();
    }
}
