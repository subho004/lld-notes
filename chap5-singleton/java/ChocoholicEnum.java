/** Second enum singleton: one constant, thread-safe and serialization/reflection-safe by the JVM. */
public enum ChocoholicEnum {
    INSTANCE;

    public void eatChocolate() {
        System.out.println("Eating chocolate");
    }
}
