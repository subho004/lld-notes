/**
 * Entry point: shows the same order handled by two Abstract Factory stores (NY and Chicago).
 */
public class PizzaShop2 {
    public static void main(String[] args) {
        PizzaStore2 nyStore = new NYPizzaStore2();
        PizzaStore2 chicagoStore = new ChicagoPizzaStore2();

        System.out.println("=== Same pizza type, different ingredient factories ===\n");

        Pizza2 pizza = nyStore.orderPizza("cheese");
        System.out.println("Ethan ordered a " + pizza.getName());
        System.out.println(pizza);

        pizza = chicagoStore.orderPizza("cheese");
        System.out.println("Joel ordered a " + pizza.getName());
        System.out.println(pizza);

        System.out.println("=== Full factory usage (veggies, pepperoni, clams) ===\n");

        pizza = nyStore.orderPizza("veggie");
        System.out.println("Ethan ordered a " + pizza.getName());
        System.out.println(pizza);

        pizza = chicagoStore.orderPizza("pepperoni");
        System.out.println("Joel ordered a " + pizza.getName());
        System.out.println(pizza);

        pizza = nyStore.orderPizza("clam");
        System.out.println("Ethan ordered a " + pizza.getName());
        System.out.println(pizza);

        pizza = chicagoStore.orderPizza("clam");
        System.out.println("Joel ordered a " + pizza.getName());
        System.out.println(pizza);
    }
}
