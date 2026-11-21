/** Client showing getInstance() always returns the same Singleton object. */
public class SingletonTest {
    public static void main(String[] args) {
        Singleton first = Singleton.getInstance();
        Singleton second = Singleton.getInstance();
        System.out.println("Same instance? " + (first == second));
    }
}
