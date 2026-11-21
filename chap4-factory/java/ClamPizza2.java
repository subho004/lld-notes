/**
 * Concrete product: stores an IngredientFactory and builds its ingredients from it in prepare(),
 * so the pizza never names a regional class.
 */
public class ClamPizza2 extends Pizza2 {
    IngredientFactory ingredientFactory;

    public ClamPizza2(IngredientFactory ingredientFactory) {
        this.ingredientFactory = ingredientFactory;
    }

    // Clam pizza: adds clams (fresh in NY, frozen in Chicago) via the factory.
    void prepare() {
        System.out.println("Preparing " + name);
        dough = ingredientFactory.createDough();
        System.out.println("  dough: " + dough);
        sauce = ingredientFactory.createSauce();
        System.out.println("  sauce: " + sauce);
        cheese = ingredientFactory.createCheese();
        System.out.println("  cheese: " + cheese);
        clams = ingredientFactory.createClam();
        System.out.println("  clams: " + clams);
    }
}
