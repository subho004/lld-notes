/**
 * Concrete Creator: factory method picks the regional IngredientFactory and injects it into the pizza.
 */
public class NYPizzaStore2 extends PizzaStore2 {

    public Pizza2 createPizza(String item) {
        Pizza2 pizza = null;
        // The regional ingredient factory, injected into the pizza so it can build its own ingredients.
        IngredientFactory ingredientFactory = new NYPizzaIngredientFactory();

        if (item.equals("cheese")) {
            pizza = new CheesePizza2(ingredientFactory);
            pizza.setName("New York Style Cheese Pizza");
        } else if (item.equals("veggie")) {
            pizza = new VeggiePizza2(ingredientFactory);
            pizza.setName("New York Style Veggie Pizza");
        } else if (item.equals("pepperoni")) {
            pizza = new PepperoniPizza2(ingredientFactory);
            pizza.setName("New York Style Pepperoni Pizza");
        } else if (item.equals("clam")) {
            pizza = new ClamPizza2(ingredientFactory);
            pizza.setName("New York Style Clam Pizza");
        }
        return pizza;
    }
}
