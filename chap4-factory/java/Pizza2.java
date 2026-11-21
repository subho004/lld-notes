/**
 * Abstract product for the Abstract Factory example. Holds ingredient objects (not strings);
 * each subclass's prepare() asks its IngredientFactory for the ones it needs.
 */
public abstract class Pizza2 {
    String name;
    Dough dough;
    Sauce sauce;
    Veggies[] veggies;
    Cheese cheese;
    Pepperoni pepperoni;
    Clams clams;

    // Each subclass decides which ingredients to request from its factory.
    abstract void prepare();

    void bake() {
        System.out.println("Bake for 25 minutes at 350");
    }

    void cut() {
        System.out.println("Cutting the pizza into diagonal slices");
    }

    void box() {
        System.out.println("Place pizza in official PizzaStore box");
    }

    void setName(String name) {
        this.name = name;
    }

    String getName() {
        return name;
    }

    // Prints only the ingredients that were set (null ones are skipped).
    public String toString() {
        StringBuilder result = new StringBuilder();
        result.append("---- " + name + " ----\n");
        if (dough != null) {
            result.append(dough + "\n");
        }
        if (sauce != null) {
            result.append(sauce + "\n");
        }
        if (cheese != null) {
            result.append(cheese + "\n");
        }
        if (veggies != null) {
            for (int i = 0; i < veggies.length; i++) {
                result.append(veggies[i]);
                if (i < veggies.length - 1) {
                    result.append(", ");
                }
            }
            result.append("\n");
        }
        if (pepperoni != null) {
            result.append(pepperoni + "\n");
        }
        if (clams != null) {
            result.append(clams + "\n");
        }
        return result.toString();
    }
}
