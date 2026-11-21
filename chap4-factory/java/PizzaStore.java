/**
 * Creator in the Factory Method pattern. orderPizza() is the fixed workflow; createPizza() is the
 * factory method that subclasses implement to choose the concrete Pizza.
 */
public abstract class PizzaStore {
    // Template-like workflow: creation is delegated to createPizza(), the rest is region-independent.
    public Pizza orderPizza(String type) {
        Pizza pizza;
        pizza = createPizza(type);
        pizza.prepare();
        pizza.bake();
        pizza.cut();
        pizza.box();
        return pizza;
    }

    // The factory method. Package-private, so only same-package subclasses can implement it.
    abstract Pizza createPizza(String type);
}
