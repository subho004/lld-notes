/**
 * Concrete product: stores an IngredientFactory and builds its ingredients from it in prepare(),
 * so the pizza never names a regional class.
 */
public class PepperoniPizza2 extends Pizza2 {
    IngredientFactory ingredientFactory;

    public PepperoniPizza2(IngredientFactory ingredientFactory) {
        this.ingredientFactory = ingredientFactory;
    }

    // Pepperoni pizza: veggies plus pepperoni from the factory.
    void prepare() {
        System.out.println("Preparing " + name);
        dough = ingredientFactory.createDough();
        System.out.println("  dough: " + dough);
        sauce = ingredientFactory.createSauce();
        System.out.println("  sauce: " + sauce);
        cheese = ingredientFactory.createCheese();
        System.out.println("  cheese: " + cheese);
        veggies = ingredientFactory.createVeggies();
        System.out.print("  veggies: ");
        for (int i = 0; i < veggies.length; i++) {
            System.out.print(veggies[i]);
            if (i < veggies.length - 1) {
                System.out.print(", ");
            }
        }
        System.out.println();
        pepperoni = ingredientFactory.createPepperoni();
        System.out.println("  pepperoni: " + pepperoni);
    }
}
