package adaptive;

/** Adapter: lets a Duck be used wherever a Turkey is expected (Duck is the adaptee). */
public class DuckAdapter implements Turkey {
    private Duck duck;

    public DuckAdapter(Duck duck) {
        this.duck = duck;
    }

        // Translation: a turkey's gobble is rendered as the duck's quack.
    public void gobble() {
        duck.quack();
    }

        // A duck flies far, a turkey only a short hop, so call duck.fly() 5 times to compensate.
    public void fly() {
        for (int i = 0; i < 5; i++) {
            duck.fly();
        }
    }

}
