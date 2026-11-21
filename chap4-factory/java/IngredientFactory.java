/**
 * Abstract Factory: one create method per ingredient, so a whole family of regional ingredients is
 * produced without the pizzas naming any concrete class.
 */
public interface IngredientFactory {
    public Dough createDough();

    public Sauce createSauce();

    public Cheese createCheese();

    public Veggies[] createVeggies();

    public Pepperoni createPepperoni();

    public Clams createClam();
}
