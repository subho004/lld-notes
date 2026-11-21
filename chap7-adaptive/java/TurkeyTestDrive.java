package adaptive;

/** Client: passes a real Turkey and a DuckAdapter to the same code; testTurkey cannot tell them apart. */
public class TurkeyTestDrive {
    public static void main(String[] args) {
        MallardDuck duck = new MallardDuck();
        WildTurkey turkey = new WildTurkey();
        Turkey duckAdapter = new DuckAdapter(duck);

        System.out.println("The Duck says...");
        testTurkey(turkey);

        System.out.println("\nThe TurkeyAdapter says...");
        testTurkey(duckAdapter);
    }

    static void testTurkey(Turkey turkey) {
        turkey.gobble();
        turkey.fly();
    }
}
