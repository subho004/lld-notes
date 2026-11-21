/** Client showing every reference to SingletonEnum.INSTANCE is identical. */
public class SingletonEnumTest {
    public static void main(String[] args) {
        SingletonEnum.INSTANCE.doSomething();
        SingletonEnum another = SingletonEnum.INSTANCE;
        System.out.println("Same instance? " + (SingletonEnum.INSTANCE == another));
    }
}
