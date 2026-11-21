/**
 * Concrete class: supplies the coffee-specific steps; also a runnable demo.
 */
public class Coffee extends CaffieneBeverage {

    void brew() {
        System.out.println("Brewing coffee");
    }

    void addCondiments() {
        System.out.println("Adding sugar and milk");
    }

    public static void main(String[] args) {
        Coffee coffee = new Coffee();
        coffee.prepareRecipe();
    }
}
