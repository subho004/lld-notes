package adaptive;

/** Adapter: lets a Turkey be used wherever a Duck is expected (Turkey is the adaptee). */
public class TurkeyAdapter implements Duck {
    private Turkey turkey;

    public TurkeyAdapter(Turkey turkey) {
        this.turkey = turkey;
    }

        // Translation: quack is delegated to the turkey's gobble.
    public void quack() {
        turkey.gobble();
    }

        // A turkey only flies a short distance, so call turkey.fly() 5 times to mimic a duck's flight.
    public void fly() {
        for (int i = 0; i < 5; i++) {
            turkey.fly();
        }
    }
}
