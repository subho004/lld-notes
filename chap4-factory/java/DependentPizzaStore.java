/**
 * The "before" picture: one class that knows every concrete pizza for every region, so it depends on
 * all of them. Factory Method (PizzaStore subclasses) removes this dependency. Has its own main().
 */
public class DependentPizzaStore {
    // Nested region/type if-else: adding a pizza or region means editing this method.
    public Pizza createPizza(String region, String type) {
        Pizza pizza = null;

        if (region.equals("NY")) {
            if (type.equals("cheese")) {
                pizza = new NYStyleCheesePizza();
            } else if (type.equals("pepperoni")) {
                pizza = new NYStylePepperoniPizza();
            } else if (type.equals("clam")) {
                pizza = new NYStyleClamPizza();
            } else if (type.equals("veggie")) {
                pizza = new NYStyleVeggiePizza();
            }
        } else if (region.equals("Chicago")) {
            if (type.equals("cheese")) {
                pizza = new ChicagoStyleCheesePizza();
            } else if (type.equals("pepperoni")) {
                pizza = new ChicagoStylePepperoniPizza();
            } else if (type.equals("clam")) {
                pizza = new ChicagoStyleClamPizza();
            }
        }

        return pizza;
    }

    public static void main(String[] args) {
        DependentPizzaStore store = new DependentPizzaStore();

        Pizza nyPizza = store.createPizza("NY", "cheese");
        nyPizza.prepare();
        System.out.println("Ordered: " + nyPizza.getName() + "\n");

        Pizza chicagoPizza = store.createPizza("Chicago", "pepperoni");
        chicagoPizza.prepare();
        System.out.println("Ordered: " + chicagoPizza.getName());
    }
}
