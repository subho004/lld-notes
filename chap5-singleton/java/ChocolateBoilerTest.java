/** Client: obtains the shared boiler twice, then runs fill, boil, drain. */
public class ChocolateBoilerTest {
    public static void main(String[] args) {
        ChocolateBoiler boiler = ChocolateBoiler.getInstance();
        ChocolateBoiler sameBoiler = ChocolateBoiler.getInstance();

        System.out.println("Same instance? " + (boiler == sameBoiler));

        boiler.fill();
        System.out.println("Empty: " + boiler.isEmpty() + ", Boiled: " + boiler.isBoiled());

        boiler.boil();
        System.out.println("Empty: " + boiler.isEmpty() + ", Boiled: " + boiler.isBoiled());

        boiler.drain();
        System.out.println("Empty: " + boiler.isEmpty() + ", Boiled: " + boiler.isBoiled());
    }
}
