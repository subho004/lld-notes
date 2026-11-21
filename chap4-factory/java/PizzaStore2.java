/**
 * Creator for the Abstract Factory example; same orderPizza() workflow as PizzaStore but with Pizza2.
 */
public abstract class PizzaStore2 {
    // Same workflow as PizzaStore; creation is delegated to the factory method below.
    public Pizza2 orderPizza(String type) {
        Pizza2 pizza = createPizza(type);
        pizza.prepare();
        pizza.bake();
        pizza.cut();
        pizza.box();
        return pizza;
    }

    // The factory method (package-private); subclasses choose the IngredientFactory and Pizza2.
    abstract Pizza2 createPizza(String type);
}
