/** Classic lazy Singleton: private constructor, static holder field, global getInstance(). */
public class Singleton {
    private static Singleton uniqueInstance;

    private Singleton() {
    }

    // synchronized makes lazy creation thread-safe, at the cost of locking on every call.
    public static synchronized Singleton getInstance() {
        if (uniqueInstance == null) {
            uniqueInstance = new Singleton();
        }
        return uniqueInstance;
    }
}