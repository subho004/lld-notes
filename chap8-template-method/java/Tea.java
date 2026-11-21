/**
 * Concrete class: supplies the tea-specific steps; also a runnable demo.
 */
public class Tea extends CaffieneBeverage {

    void brew() {
        System.out.println("Steeping tea bag");
    }

    void addCondiments() {
        System.out.println("Adding lemon");
    }

    public static void main(String[] args) {
        Tea tea = new Tea();
        tea.prepareRecipe();
    }
}
