/** Singleton using double-checked locking; state-changing methods are synchronized. */
public class ChocolateBoiler {
    // volatile is required so other threads never see a partially constructed instance.
    private static volatile ChocolateBoiler uniqueInstance;
    private boolean empty;
    private boolean boiled;

    private ChocolateBoiler() {
        empty = true;
        boiled = false;
    }

    public static ChocolateBoiler getInstance() {
        // First check avoids locking once created; second check guards the race inside the lock.
        if (uniqueInstance == null) {
            synchronized (ChocolateBoiler.class) {
                if (uniqueInstance == null) {
                    uniqueInstance = new ChocolateBoiler();
                }
            }
        }
        return uniqueInstance;
    }

    // Guards below keep the boiler consistent: fill only when empty, boil only when full and unboiled, drain only when boiled.
    public synchronized void fill() {
        if (isEmpty()) {
            empty = false;
            boiled = false;
        }
    }

    public synchronized void drain() {
        if (!isEmpty() && isBoiled()) {
            empty = true;
        }
    }

    public synchronized void boil() {
        if (!isEmpty() && !isBoiled()) {
            boiled = true;
        }
    }

    public synchronized boolean isEmpty() {
        return empty;
    }

    public synchronized boolean isBoiled() {
        return boiled;
    }
}
