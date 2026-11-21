/**
 * Concrete product: stores an IngredientFactory and builds its ingredients from it in prepare(),
 * so the pizza never names a regional class.
 */
public class CheesePizza2 extends Pizza2 {
    IngredientFactory ingredientFactory;

    public CheesePizza2(IngredientFactory ingredientFactory) {
        this.ingredientFactory = ingredientFactory;
    }

    // Cheese pizza: dough, sauce and cheese from the factory.
    void prepare() {
        System.out.println("Preparing " + name);
        dough = ingredientFactory.createDough();
        System.out.println("  dough: " + dough);
        sauce = ingredientFactory.createSauce();
        System.out.println("  sauce: " + sauce);
        cheese = ingredientFactory.createCheese();
        System.out.println("  cheese: " + cheese);
    }
}
