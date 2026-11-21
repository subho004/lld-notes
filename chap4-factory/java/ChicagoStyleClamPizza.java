/**
 * Concrete product created by ChicagoStyle stores; overrides cut() for square slices.
 * There is no Chicago veggie pizza (DependentPizzaStore returns null for it).
 */
public class ChicagoStyleClamPizza extends Pizza {
    public ChicagoStyleClamPizza() {
        name = "Chicago Style Deep Dish Clam Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";
        toppings.add("Shredded Mozzarella Cheese");
        toppings.add("Fresh Clams");
    }

    public void cut() {
        System.out.println("Cutting the pizza into square slices");
    }
}
