/**
 * Abstract class with a template method that includes a hook
 * (customerWantsCondiments) to optionally skip a step.
 */
public abstract class CaffeineBeverageWithHook {
    /** Template method; final so the step order is fixed. The hook decides whether addCondiments() runs. */
    final void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments()) {
            addCondiments();
        }
    }

    // Abstract steps implemented by subclasses.
    abstract void brew();

    abstract void addCondiments();

    void boilWater() {
        System.out.println("Boiling water");
    }

    void pourInCup() {
        System.out.println("Pouring into cup");
    }

    /** Hook: default is "yes"; subclasses may override to change the flow. */
    boolean customerWantsCondiments() {
        return true;
    }
}
