/** Enum singleton (preferred Java idiom): INSTANCE is created once by the JVM. */
public enum SingletonEnum {
    INSTANCE;

    public void doSomething() {
        System.out.println("SingletonEnum");
    }
}
