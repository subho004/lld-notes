package leastknowledge;

/** Component owned by Car; clients never reach it directly. */
public class Doors {
    private boolean locked;

    public void lock() {
        locked = true;
        System.out.println("Doors locked");
    }

    public void unlock() {
        locked = false;
        System.out.println("Doors unlocked");
    }

    public boolean isLocked() {
        return locked;
    }
}
