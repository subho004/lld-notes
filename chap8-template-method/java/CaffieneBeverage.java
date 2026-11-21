/**
 * Abstract class holding the template method (prepareRecipe).
 * Note: the file/class name "Caffiene" is a typo kept consistently across the repo.
 */
public abstract class CaffieneBeverage {
    /** Template method: fixed algorithm skeleton; final so subclasses cannot reorder the steps. */
    final void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

    // Steps that subclasses must supply.
    abstract void brew();

    abstract void addCondiments();

    // Steps shared by all beverages, implemented once here.
    void boilWater() {
        System.out.println("Boiling water");
    }

    void pourInCup() {
        System.out.println("Pouring into cup");
    }
}
